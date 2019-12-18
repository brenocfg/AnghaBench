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
struct TYPE_2__ {int /*<<< orphan*/  be_alloc; } ;
struct xen_drm_front_info {int /*<<< orphan*/  xb_dev; TYPE_1__ cfg; int /*<<< orphan*/  dbuf_list; struct xen_drm_front_drm_info* drm_info; } ;
struct xen_drm_front_drm_info {struct drm_device* drm_dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XenbusStateInitialising ; 
 int /*<<< orphan*/  dbuf_free_all (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_dev_is_unplugged (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unplug (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  xen_drm_front_evtchnl_free_all (struct xen_drm_front_info*) ; 
 int /*<<< orphan*/  xenbus_switch_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_drm_drv_fini(struct xen_drm_front_info *front_info)
{
	struct xen_drm_front_drm_info *drm_info = front_info->drm_info;
	struct drm_device *dev;

	if (!drm_info)
		return;

	dev = drm_info->drm_dev;
	if (!dev)
		return;

	/* Nothing to do if device is already unplugged */
	if (drm_dev_is_unplugged(dev))
		return;

	drm_kms_helper_poll_fini(dev);
	drm_dev_unplug(dev);
	drm_dev_put(dev);

	front_info->drm_info = NULL;

	xen_drm_front_evtchnl_free_all(front_info);
	dbuf_free_all(&front_info->dbuf_list);

	/*
	 * If we are not using backend allocated buffers, then tell the
	 * backend we are ready to (re)initialize. Otherwise, wait for
	 * drm_driver.release.
	 */
	if (!front_info->cfg.be_alloc)
		xenbus_switch_state(front_info->xb_dev,
				    XenbusStateInitialising);
}