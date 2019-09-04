#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__ rlc; } ;
struct amdgpu_device {TYPE_3__ gfx; int /*<<< orphan*/  grbm_idx_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* exit_safe_mode ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* enter_safe_mode ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  SEEDCCtrlForceStallConfig_Vega10 ; 
 int /*<<< orphan*/  SEEDCForceStallPatternConfig_Vega10 ; 
 int /*<<< orphan*/  VEGA10_CONFIGREG_DIDT ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vega10_didt_set_mask (struct pp_hwmgr*,int) ; 
 int vega10_program_didt_config_registers (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_enable_se_edc_force_stall_config(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;
	int result;

	adev->gfx.rlc.funcs->enter_safe_mode(adev);

	mutex_lock(&adev->grbm_idx_mutex);
	WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, 0xE0000000);
	mutex_unlock(&adev->grbm_idx_mutex);

	result = vega10_program_didt_config_registers(hwmgr, SEEDCForceStallPatternConfig_Vega10, VEGA10_CONFIGREG_DIDT);
	result |= vega10_program_didt_config_registers(hwmgr, SEEDCCtrlForceStallConfig_Vega10, VEGA10_CONFIGREG_DIDT);
	if (0 != result)
		return result;

	vega10_didt_set_mask(hwmgr, false);

	adev->gfx.rlc.funcs->exit_safe_mode(adev);

	return 0;
}