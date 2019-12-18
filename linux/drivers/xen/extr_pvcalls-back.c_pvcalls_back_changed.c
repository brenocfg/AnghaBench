#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xenbus_device {int /*<<< orphan*/  dev; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  XenbusStateClosed 133 
#define  XenbusStateClosing 132 
#define  XenbusStateConnected 131 
 int const XenbusStateInitWait ; 
#define  XenbusStateInitialised 130 
#define  XenbusStateInitialising 129 
#define  XenbusStateUnknown 128 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_backend_state (struct xenbus_device*,int const) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xenbus_dev_is_online (struct xenbus_device*) ; 

__attribute__((used)) static void pvcalls_back_changed(struct xenbus_device *dev,
				 enum xenbus_state frontend_state)
{
	switch (frontend_state) {
	case XenbusStateInitialising:
		set_backend_state(dev, XenbusStateInitWait);
		break;

	case XenbusStateInitialised:
	case XenbusStateConnected:
		set_backend_state(dev, XenbusStateConnected);
		break;

	case XenbusStateClosing:
		set_backend_state(dev, XenbusStateClosing);
		break;

	case XenbusStateClosed:
		set_backend_state(dev, XenbusStateClosed);
		if (xenbus_dev_is_online(dev))
			break;
		device_unregister(&dev->dev);
		break;
	case XenbusStateUnknown:
		set_backend_state(dev, XenbusStateClosed);
		device_unregister(&dev->dev);
		break;

	default:
		xenbus_dev_fatal(dev, -EINVAL, "saw state %d at frontend",
				 frontend_state);
		break;
	}
}