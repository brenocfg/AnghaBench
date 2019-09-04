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
struct radeon_mode_info {scalar_t__* crtcs; } ;
struct radeon_device {int num_crtc; struct radeon_mode_info mode_info; } ;
struct radeon_crtc {scalar_t__ crtc_id; } ;
struct igp_power_info {int refresh_rate; scalar_t__ crtc_id; } ;
struct TYPE_2__ {scalar_t__ vtotal; scalar_t__ htotal; } ;
struct drm_crtc {TYPE_1__ mode; scalar_t__ enabled; } ;

/* Variables and functions */
 int drm_mode_vrefresh (TYPE_1__*) ; 
 struct igp_power_info* rs780_get_pi (struct radeon_device*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void rs780_get_pm_mode_parameters(struct radeon_device *rdev)
{
	struct igp_power_info *pi = rs780_get_pi(rdev);
	struct radeon_mode_info *minfo = &rdev->mode_info;
	struct drm_crtc *crtc;
	struct radeon_crtc *radeon_crtc;
	int i;

	/* defaults */
	pi->crtc_id = 0;
	pi->refresh_rate = 60;

	for (i = 0; i < rdev->num_crtc; i++) {
		crtc = (struct drm_crtc *)minfo->crtcs[i];
		if (crtc && crtc->enabled) {
			radeon_crtc = to_radeon_crtc(crtc);
			pi->crtc_id = radeon_crtc->crtc_id;
			if (crtc->mode.htotal && crtc->mode.vtotal)
				pi->refresh_rate = drm_mode_vrefresh(&crtc->mode);
			break;
		}
	}
}