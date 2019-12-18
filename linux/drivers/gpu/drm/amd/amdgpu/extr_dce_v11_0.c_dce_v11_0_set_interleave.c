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
typedef  int /*<<< orphan*/  u32 ;
struct drm_display_mode {int flags; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {scalar_t__ crtc_offset; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  INTERLEAVE_EN ; 
 int /*<<< orphan*/  LB_DATA_FORMAT ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mmLB_DATA_FORMAT ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void dce_v11_0_set_interleave(struct drm_crtc *crtc,
				     struct drm_display_mode *mode)
{
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	u32 tmp;

	tmp = RREG32(mmLB_DATA_FORMAT + amdgpu_crtc->crtc_offset);
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		tmp = REG_SET_FIELD(tmp, LB_DATA_FORMAT, INTERLEAVE_EN, 1);
	else
		tmp = REG_SET_FIELD(tmp, LB_DATA_FORMAT, INTERLEAVE_EN, 0);
	WREG32(mmLB_DATA_FORMAT + amdgpu_crtc->crtc_offset, tmp);
}