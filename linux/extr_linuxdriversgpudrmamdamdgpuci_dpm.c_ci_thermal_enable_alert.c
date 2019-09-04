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
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int CG_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK ; 
 int CG_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_Thermal_Cntl_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_Thermal_Cntl_Enable ; 
 scalar_t__ PPSMC_Result_OK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixCG_THERMAL_INT ; 

__attribute__((used)) static int ci_thermal_enable_alert(struct amdgpu_device *adev,
				   bool enable)
{
	u32 thermal_int = RREG32_SMC(ixCG_THERMAL_INT);
	PPSMC_Result result;

	if (enable) {
		thermal_int &= ~(CG_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK |
				 CG_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK);
		WREG32_SMC(ixCG_THERMAL_INT, thermal_int);
		result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_Thermal_Cntl_Enable);
		if (result != PPSMC_Result_OK) {
			DRM_DEBUG_KMS("Could not enable thermal interrupts.\n");
			return -EINVAL;
		}
	} else {
		thermal_int |= CG_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK |
			CG_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK;
		WREG32_SMC(ixCG_THERMAL_INT, thermal_int);
		result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_Thermal_Cntl_Disable);
		if (result != PPSMC_Result_OK) {
			DRM_DEBUG_KMS("Could not disable thermal interrupts.\n");
			return -EINVAL;
		}
	}

	return 0;
}