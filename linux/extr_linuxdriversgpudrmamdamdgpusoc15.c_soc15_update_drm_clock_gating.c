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
 int AMD_CG_SUPPORT_DRM_MGCG ; 
 int /*<<< orphan*/  MP0 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmMP0_MISC_CGTT_CTRL0 ; 

__attribute__((used)) static void soc15_update_drm_clock_gating(struct amdgpu_device *adev, bool enable)
{
	uint32_t def, data;

	def = data = RREG32(SOC15_REG_OFFSET(MP0, 0, mmMP0_MISC_CGTT_CTRL0));

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_DRM_MGCG))
		data &= ~(0x01000000 |
			  0x02000000 |
			  0x04000000 |
			  0x08000000 |
			  0x10000000 |
			  0x20000000 |
			  0x40000000 |
			  0x80000000);
	else
		data |= (0x01000000 |
			 0x02000000 |
			 0x04000000 |
			 0x08000000 |
			 0x10000000 |
			 0x20000000 |
			 0x40000000 |
			 0x80000000);

	if (def != data)
		WREG32(SOC15_REG_OFFSET(MP0, 0, mmMP0_MISC_CGTT_CTRL0), data);
}