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
struct radeon_crtc {scalar_t__ crtc_offset; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ RADEON_OVR_CLR ; 
 scalar_t__ RADEON_OVR_WID_LEFT_RIGHT ; 
 scalar_t__ RADEON_OVR_WID_TOP_BOTTOM ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void radeon_overscan_setup(struct drm_crtc *crtc,
				  struct drm_display_mode *mode)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	WREG32(RADEON_OVR_CLR + radeon_crtc->crtc_offset, 0);
	WREG32(RADEON_OVR_WID_LEFT_RIGHT + radeon_crtc->crtc_offset, 0);
	WREG32(RADEON_OVR_WID_TOP_BOTTOM + radeon_crtc->crtc_offset, 0);
}