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
struct xen_drm_front_info {int /*<<< orphan*/  xb_dev; int /*<<< orphan*/  drm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  XenbusStateReconfiguring ; 
 int /*<<< orphan*/  xen_drm_drv_fini (struct xen_drm_front_info*) ; 
 int /*<<< orphan*/  xenbus_switch_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void displback_disconnect(struct xen_drm_front_info *front_info)
{
	if (!front_info->drm_info)
		return;

	/* Tell the backend to wait until we release the DRM driver. */
	xenbus_switch_state(front_info->xb_dev, XenbusStateReconfiguring);

	xen_drm_drv_fini(front_info);
}