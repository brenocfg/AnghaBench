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
struct pp_hwmgr {int /*<<< orphan*/  device; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AvfsPSMResetConfig_vega10 ; 
 int /*<<< orphan*/  PHM_PlatformCaps_GCEDC ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PSM ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_enter_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_exit_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmGC_EDC_CTRL ; 
 int /*<<< orphan*/  vega10_didt_set_mask (struct pp_hwmgr*,int) ; 
 int /*<<< orphan*/  vega10_program_gc_didt_config_registers (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_disable_psm_gc_edc_config(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t data;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	vega10_didt_set_mask(hwmgr, false);

	amdgpu_gfx_rlc_exit_safe_mode(adev);

	if (PP_CAP(PHM_PlatformCaps_GCEDC)) {
		data = 0x00000000;
		cgs_write_register(hwmgr->device, mmGC_EDC_CTRL, data);
	}

	if (PP_CAP(PHM_PlatformCaps_PSM))
		vega10_program_gc_didt_config_registers(hwmgr,  AvfsPSMResetConfig_vega10);

	return 0;
}