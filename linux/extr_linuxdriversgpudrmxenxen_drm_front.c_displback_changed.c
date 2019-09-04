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
struct xenbus_device {int state; int /*<<< orphan*/  dev; } ;
struct xen_drm_front_info {int dummy; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  XenbusStateClosed 136 
#define  XenbusStateClosing 135 
#define  XenbusStateConnected 134 
#define  XenbusStateInitWait 133 
#define  XenbusStateInitialised 132 
#define  XenbusStateInitialising 131 
#define  XenbusStateReconfigured 130 
#define  XenbusStateReconfiguring 129 
#define  XenbusStateUnknown 128 
 struct xen_drm_front_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int displback_connect (struct xen_drm_front_info*) ; 
 int /*<<< orphan*/  displback_disconnect (struct xen_drm_front_info*) ; 
 int displback_initwait (struct xen_drm_front_info*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int /*<<< orphan*/  xenbus_strstate (int) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int const) ; 

__attribute__((used)) static void displback_changed(struct xenbus_device *xb_dev,
			      enum xenbus_state backend_state)
{
	struct xen_drm_front_info *front_info = dev_get_drvdata(&xb_dev->dev);
	int ret;

	DRM_DEBUG("Backend state is %s, front is %s\n",
		  xenbus_strstate(backend_state),
		  xenbus_strstate(xb_dev->state));

	switch (backend_state) {
	case XenbusStateReconfiguring:
		/* fall through */
	case XenbusStateReconfigured:
		/* fall through */
	case XenbusStateInitialised:
		break;

	case XenbusStateInitialising:
		if (xb_dev->state == XenbusStateReconfiguring)
			break;

		/* recovering after backend unexpected closure */
		displback_disconnect(front_info);
		break;

	case XenbusStateInitWait:
		if (xb_dev->state == XenbusStateReconfiguring)
			break;

		/* recovering after backend unexpected closure */
		displback_disconnect(front_info);
		if (xb_dev->state != XenbusStateInitialising)
			break;

		ret = displback_initwait(front_info);
		if (ret < 0)
			xenbus_dev_fatal(xb_dev, ret, "initializing frontend");
		else
			xenbus_switch_state(xb_dev, XenbusStateInitialised);
		break;

	case XenbusStateConnected:
		if (xb_dev->state != XenbusStateInitialised)
			break;

		ret = displback_connect(front_info);
		if (ret < 0) {
			displback_disconnect(front_info);
			xenbus_dev_fatal(xb_dev, ret, "connecting backend");
		} else {
			xenbus_switch_state(xb_dev, XenbusStateConnected);
		}
		break;

	case XenbusStateClosing:
		/*
		 * in this state backend starts freeing resources,
		 * so let it go into closed state, so we can also
		 * remove ours
		 */
		break;

	case XenbusStateUnknown:
		/* fall through */
	case XenbusStateClosed:
		if (xb_dev->state == XenbusStateClosed)
			break;

		displback_disconnect(front_info);
		break;
	}
}