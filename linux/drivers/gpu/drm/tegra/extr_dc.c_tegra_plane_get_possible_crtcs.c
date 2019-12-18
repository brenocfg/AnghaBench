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
struct TYPE_2__ {int num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long tegra_plane_get_possible_crtcs(struct drm_device *drm)
{
	/*
	 * Ideally this would use drm_crtc_mask(), but that would require the
	 * CRTC to already be in the mode_config's list of CRTCs. However, it
	 * will only be added to that list in the drm_crtc_init_with_planes()
	 * (in tegra_dc_init()), which in turn requires registration of these
	 * planes. So we have ourselves a nice little chicken and egg problem
	 * here.
	 *
	 * We work around this by manually creating the mask from the number
	 * of CRTCs that have been registered, and should therefore always be
	 * the same as drm_crtc_index() after registration.
	 */
	return 1 << drm->mode_config.num_crtc;
}