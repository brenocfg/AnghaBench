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
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {int /*<<< orphan*/  enabled; struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 int /*<<< orphan*/  avivo_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  dce4_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  dce5_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  legacy_crtc_load_lut (struct drm_crtc*) ; 

void radeon_crtc_load_lut(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;

	if (!crtc->enabled)
		return;

	if (ASIC_IS_DCE5(rdev))
		dce5_crtc_load_lut(crtc);
	else if (ASIC_IS_DCE4(rdev))
		dce4_crtc_load_lut(crtc);
	else if (ASIC_IS_AVIVO(rdev))
		avivo_crtc_load_lut(crtc);
	else
		legacy_crtc_load_lut(crtc);
}