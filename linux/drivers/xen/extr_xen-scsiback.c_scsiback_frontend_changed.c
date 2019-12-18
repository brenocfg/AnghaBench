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
struct xenbus_device {int const state; int /*<<< orphan*/  dev; } ;
struct vscsibk_info {int /*<<< orphan*/  irq; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  VSCSIBACK_OP_ADD_OR_DEL_LUN ; 
 int /*<<< orphan*/  VSCSIBACK_OP_UPDATEDEV_STATE ; 
#define  XenbusStateClosed 134 
#define  XenbusStateClosing 133 
#define  XenbusStateConnected 132 
#define  XenbusStateInitialised 131 
#define  XenbusStateInitialising 130 
 int const XenbusStateReconfigured ; 
#define  XenbusStateReconfiguring 129 
#define  XenbusStateUnknown 128 
 struct vscsibk_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsiback_disconnect (struct vscsibk_info*) ; 
 int /*<<< orphan*/  scsiback_do_lun_hotplug (struct vscsibk_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsiback_map (struct vscsibk_info*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xenbus_dev_is_online (struct xenbus_device*) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int const) ; 

__attribute__((used)) static void scsiback_frontend_changed(struct xenbus_device *dev,
					enum xenbus_state frontend_state)
{
	struct vscsibk_info *info = dev_get_drvdata(&dev->dev);

	switch (frontend_state) {
	case XenbusStateInitialising:
		break;

	case XenbusStateInitialised:
		if (scsiback_map(info))
			break;

		scsiback_do_lun_hotplug(info, VSCSIBACK_OP_ADD_OR_DEL_LUN);
		xenbus_switch_state(dev, XenbusStateConnected);
		break;

	case XenbusStateConnected:
		scsiback_do_lun_hotplug(info, VSCSIBACK_OP_UPDATEDEV_STATE);

		if (dev->state == XenbusStateConnected)
			break;

		xenbus_switch_state(dev, XenbusStateConnected);
		break;

	case XenbusStateClosing:
		if (info->irq)
			scsiback_disconnect(info);

		xenbus_switch_state(dev, XenbusStateClosing);
		break;

	case XenbusStateClosed:
		xenbus_switch_state(dev, XenbusStateClosed);
		if (xenbus_dev_is_online(dev))
			break;
		/* fall through - if not online */
	case XenbusStateUnknown:
		device_unregister(&dev->dev);
		break;

	case XenbusStateReconfiguring:
		scsiback_do_lun_hotplug(info, VSCSIBACK_OP_ADD_OR_DEL_LUN);
		xenbus_switch_state(dev, XenbusStateReconfigured);

		break;

	default:
		xenbus_dev_fatal(dev, -EINVAL, "saw state %d at frontend",
					frontend_state);
		break;
	}
}