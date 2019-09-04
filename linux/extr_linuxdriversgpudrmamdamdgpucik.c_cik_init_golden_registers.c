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
struct amdgpu_device {int asic_type; int /*<<< orphan*/  grbm_idx_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CHIP_BONAIRE 132 
#define  CHIP_HAWAII 131 
#define  CHIP_KABINI 130 
#define  CHIP_KAVERI 129 
#define  CHIP_MULLINS 128 
 int /*<<< orphan*/  amdgpu_device_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bonaire_golden_common_registers ; 
 int /*<<< orphan*/  bonaire_golden_registers ; 
 int /*<<< orphan*/  bonaire_golden_spm_registers ; 
 int /*<<< orphan*/  bonaire_mgcg_cgcg_init ; 
 int /*<<< orphan*/  godavari_golden_registers ; 
 int /*<<< orphan*/  hawaii_golden_common_registers ; 
 int /*<<< orphan*/  hawaii_golden_registers ; 
 int /*<<< orphan*/  hawaii_golden_spm_registers ; 
 int /*<<< orphan*/  hawaii_mgcg_cgcg_init ; 
 int /*<<< orphan*/  kalindi_golden_common_registers ; 
 int /*<<< orphan*/  kalindi_golden_registers ; 
 int /*<<< orphan*/  kalindi_golden_spm_registers ; 
 int /*<<< orphan*/  kalindi_mgcg_cgcg_init ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spectre_golden_common_registers ; 
 int /*<<< orphan*/  spectre_golden_registers ; 
 int /*<<< orphan*/  spectre_golden_spm_registers ; 
 int /*<<< orphan*/  spectre_mgcg_cgcg_init ; 

__attribute__((used)) static void cik_init_golden_registers(struct amdgpu_device *adev)
{
	/* Some of the registers might be dependent on GRBM_GFX_INDEX */
	mutex_lock(&adev->grbm_idx_mutex);

	switch (adev->asic_type) {
	case CHIP_BONAIRE:
		amdgpu_device_program_register_sequence(adev,
							bonaire_mgcg_cgcg_init,
							ARRAY_SIZE(bonaire_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							bonaire_golden_registers,
							ARRAY_SIZE(bonaire_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							bonaire_golden_common_registers,
							ARRAY_SIZE(bonaire_golden_common_registers));
		amdgpu_device_program_register_sequence(adev,
							bonaire_golden_spm_registers,
							ARRAY_SIZE(bonaire_golden_spm_registers));
		break;
	case CHIP_KABINI:
		amdgpu_device_program_register_sequence(adev,
							kalindi_mgcg_cgcg_init,
							ARRAY_SIZE(kalindi_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							kalindi_golden_registers,
							ARRAY_SIZE(kalindi_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							kalindi_golden_common_registers,
							ARRAY_SIZE(kalindi_golden_common_registers));
		amdgpu_device_program_register_sequence(adev,
							kalindi_golden_spm_registers,
							ARRAY_SIZE(kalindi_golden_spm_registers));
		break;
	case CHIP_MULLINS:
		amdgpu_device_program_register_sequence(adev,
							kalindi_mgcg_cgcg_init,
							ARRAY_SIZE(kalindi_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							godavari_golden_registers,
							ARRAY_SIZE(godavari_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							kalindi_golden_common_registers,
							ARRAY_SIZE(kalindi_golden_common_registers));
		amdgpu_device_program_register_sequence(adev,
							kalindi_golden_spm_registers,
							ARRAY_SIZE(kalindi_golden_spm_registers));
		break;
	case CHIP_KAVERI:
		amdgpu_device_program_register_sequence(adev,
							spectre_mgcg_cgcg_init,
							ARRAY_SIZE(spectre_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							spectre_golden_registers,
							ARRAY_SIZE(spectre_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							spectre_golden_common_registers,
							ARRAY_SIZE(spectre_golden_common_registers));
		amdgpu_device_program_register_sequence(adev,
							spectre_golden_spm_registers,
							ARRAY_SIZE(spectre_golden_spm_registers));
		break;
	case CHIP_HAWAII:
		amdgpu_device_program_register_sequence(adev,
							hawaii_mgcg_cgcg_init,
							ARRAY_SIZE(hawaii_mgcg_cgcg_init));
		amdgpu_device_program_register_sequence(adev,
							hawaii_golden_registers,
							ARRAY_SIZE(hawaii_golden_registers));
		amdgpu_device_program_register_sequence(adev,
							hawaii_golden_common_registers,
							ARRAY_SIZE(hawaii_golden_common_registers));
		amdgpu_device_program_register_sequence(adev,
							hawaii_golden_spm_registers,
							ARRAY_SIZE(hawaii_golden_spm_registers));
		break;
	default:
		break;
	}
	mutex_unlock(&adev->grbm_idx_mutex);
}