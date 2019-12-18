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
typedef  int uint32_t ;
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_DRM_LS ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 

__attribute__((used)) static void vi_update_drm_light_sleep(struct amdgpu_device *adev,
				      bool enable)
{
	uint32_t temp, data;

	temp = data = RREG32(0x157a);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_DRM_LS))
		data |= 1;
	else
		data &= ~1;

	if (temp != data)
		WREG32(0x157a, data);
}