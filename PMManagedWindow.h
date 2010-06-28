/**
 * Étoilé ProjectManager - PMDecoratedWindow.h
 *
 * Copyright (C) 2009 David Chisnall
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **/
#import "XCBWindow.h"

typedef enum _PMManagedWindowState
{
	/**
	  * The managed window is waiting on the child to move
	  * to the available state so that it can figure out
	  * mapping behaviour.
	  */
	PMManagedWindowPendingState,
	/**
	  * An "unknown" state, where the managed window is
	  * waiting for all the child properties to be cached
	  * before transitioning into the withdrawn/iconic/normal
	  * states
	  */
	PMManagedWindowWaitingOnPropertiesState,
	PMManagedWindowWithdrawnState,
	PMManagedWindowIconicState,
	PMManagedWindowNormalState
} PMManagedWindowState;

@interface PMManagedWindow : NSObject {
	id delegate;
	XCBWindow *child;
	XCBWindow *decorationWindow;
	PMManagedWindowState state;

	XCBPoint child_origin;

	// Fields containing pending events
	NSArray* pendingEvents;

	// Fields used during map and unmap transitions
	NSMutableSet *pendingWindowProperties;
	BOOL ignoreUnmap;
	BOOL reparented;
}
- (id)initWithChildWindow: (XCBWindow*)win pendingEvents: (NSArray*)pending;
- (XCBWindow*)childWindow;
- (XCBWindow*)decorationWindow;
- (void)setDelegate: (id)delegate;
@end

@interface NSObject (PMManagedWindowDelegate)
- (void)managedWindowWithdrawn: (PMManagedWindow*)managedWindow;
@end