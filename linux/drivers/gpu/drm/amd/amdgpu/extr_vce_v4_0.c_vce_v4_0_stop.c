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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCE ; 
 int VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mmVCE_SOFT_RESET ; 
 int /*<<< orphan*/  mmVCE_STATUS ; 
 int /*<<< orphan*/  mmVCE_VCPU_CNTL ; 

__attribute__((used)) static int vce_v4_0_stop(struct amdgpu_device *adev)
{

	/* Disable VCPU */
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CNTL), 0, ~0x200001);

	/* hold on ECPU */
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_SOFT_RESET),
			VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK,
			~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK);

	/* clear VCE_STATUS */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS), 0);

	/* Set Clock-Gating off */
	/* if (adev->cg_flags & AMD_CG_SUPPORT_VCE_MGCG)
		vce_v4_0_set_vce_sw_clock_gating(adev, false);
	*/

	return 0;
}