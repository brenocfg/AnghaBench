#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xenbus_device {int state; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;
struct TYPE_2__ {int /*<<< orphan*/  frontends_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
#define  XenbusStateClosed 132 
#define  XenbusStateClosing 131 
#define  XenbusStateConnected 130 
#define  XenbusStateInitWait 129 
#define  XenbusStateInitialised 128 
 int /*<<< orphan*/  backend_connect (struct xenbus_device*) ; 
 int /*<<< orphan*/  backend_disconnect (struct xenbus_device*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 TYPE_1__ pvcalls_back_global ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int const) ; 

__attribute__((used)) static void set_backend_state(struct xenbus_device *dev,
			      enum xenbus_state state)
{
	while (dev->state != state) {
		switch (dev->state) {
		case XenbusStateClosed:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateConnected:
				xenbus_switch_state(dev, XenbusStateInitWait);
				break;
			case XenbusStateClosing:
				xenbus_switch_state(dev, XenbusStateClosing);
				break;
			default:
				WARN_ON(1);
			}
			break;
		case XenbusStateInitWait:
		case XenbusStateInitialised:
			switch (state) {
			case XenbusStateConnected:
				backend_connect(dev);
				xenbus_switch_state(dev, XenbusStateConnected);
				break;
			case XenbusStateClosing:
			case XenbusStateClosed:
				xenbus_switch_state(dev, XenbusStateClosing);
				break;
			default:
				WARN_ON(1);
			}
			break;
		case XenbusStateConnected:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateClosing:
			case XenbusStateClosed:
				down(&pvcalls_back_global.frontends_lock);
				backend_disconnect(dev);
				up(&pvcalls_back_global.frontends_lock);
				xenbus_switch_state(dev, XenbusStateClosing);
				break;
			default:
				WARN_ON(1);
			}
			break;
		case XenbusStateClosing:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateConnected:
			case XenbusStateClosed:
				xenbus_switch_state(dev, XenbusStateClosed);
				break;
			default:
				WARN_ON(1);
			}
			break;
		default:
			WARN_ON(1);
		}
	}
}