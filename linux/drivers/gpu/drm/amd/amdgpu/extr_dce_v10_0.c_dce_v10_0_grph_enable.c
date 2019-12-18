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
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {scalar_t__ crtc_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ mmGRPH_ENABLE ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void dce_v10_0_grph_enable(struct drm_crtc *crtc, bool enable)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;

	if (enable)
		WREG32(mmGRPH_ENABLE + amdgpu_crtc->crtc_offset, 1);
	else
		WREG32(mmGRPH_ENABLE + amdgpu_crtc->crtc_offset, 0);
}