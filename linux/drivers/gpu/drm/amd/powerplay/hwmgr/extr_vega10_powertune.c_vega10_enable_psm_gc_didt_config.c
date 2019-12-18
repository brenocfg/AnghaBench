#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_3__ {int max_shader_engines; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {int /*<<< orphan*/  grbm_idx_mutex; TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AvfsPSMInitConfig_vega10 ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  GCDiDtCtrl0Config_vega10 ; 
 int /*<<< orphan*/  GCDiDtDroopCtrlConfig_vega10 ; 
 int GRBM_GFX_INDEX__INSTANCE_BROADCAST_WRITES_MASK ; 
 int GRBM_GFX_INDEX__SE_INDEX__SHIFT ; 
 int GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK ; 
 int /*<<< orphan*/  PHM_PlatformCaps_GCEDC ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PSM ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEDiDtCtrl0Config_Vega10 ; 
 int /*<<< orphan*/  SEDiDtCtrl3Config_vega10 ; 
 int /*<<< orphan*/  SEDiDtStallCtrlConfig_vega10 ; 
 int /*<<< orphan*/  SEDiDtStallPatternConfig_vega10 ; 
 int /*<<< orphan*/  VEGA10_CONFIGREG_DIDT ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_enter_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_exit_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vega10_didt_set_mask (struct pp_hwmgr*,int) ; 
 int vega10_program_didt_config_registers (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega10_program_gc_didt_config_registers (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_enable_psm_gc_didt_config(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;
	int result;
	uint32_t num_se = 0, count, data;

	num_se = adev->gfx.config.max_shader_engines;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	mutex_lock(&adev->grbm_idx_mutex);
	for (count = 0; count < num_se; count++) {
		data = GRBM_GFX_INDEX__INSTANCE_BROADCAST_WRITES_MASK | GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK | ( count << GRBM_GFX_INDEX__SE_INDEX__SHIFT);
		WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, data);

		result = vega10_program_didt_config_registers(hwmgr, SEDiDtStallCtrlConfig_vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_registers(hwmgr, SEDiDtStallPatternConfig_vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_registers(hwmgr, SEDiDtCtrl3Config_vega10, VEGA10_CONFIGREG_DIDT);
		result |= vega10_program_didt_config_registers(hwmgr, SEDiDtCtrl0Config_Vega10, VEGA10_CONFIGREG_DIDT);
		if (0 != result)
			break;
	}
	WREG32_SOC15(GC, 0, mmGRBM_GFX_INDEX, 0xE0000000);
	mutex_unlock(&adev->grbm_idx_mutex);

	vega10_didt_set_mask(hwmgr, true);

	amdgpu_gfx_rlc_exit_safe_mode(adev);

	vega10_program_gc_didt_config_registers(hwmgr, GCDiDtDroopCtrlConfig_vega10);
	if (PP_CAP(PHM_PlatformCaps_GCEDC))
		vega10_program_gc_didt_config_registers(hwmgr, GCDiDtCtrl0Config_vega10);

	if (PP_CAP(PHM_PlatformCaps_PSM))
		vega10_program_gc_didt_config_registers(hwmgr,  AvfsPSMInitConfig_vega10);

	return 0;
}