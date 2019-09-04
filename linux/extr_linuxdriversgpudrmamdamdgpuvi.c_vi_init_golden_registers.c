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
#define  CHIP_CARRIZO 136 
#define  CHIP_FIJI 135 
#define  CHIP_POLARIS10 134 
#define  CHIP_POLARIS11 133 
#define  CHIP_POLARIS12 132 
#define  CHIP_STONEY 131 
#define  CHIP_TONGA 130 
#define  CHIP_TOPAZ 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  amdgpu_device_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cz_mgcg_cgcg_init ; 
 int /*<<< orphan*/  fiji_mgcg_cgcg_init ; 
 int /*<<< orphan*/  iceland_mgcg_cgcg_init ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stoney_mgcg_cgcg_init ; 
 int /*<<< orphan*/  tonga_mgcg_cgcg_init ; 
 int /*<<< orphan*/  xgpu_vi_init_golden_registers (struct amdgpu_device*) ; 

__attribute__((used)) static void vi_init_golden_registers(struct amdgpu_device *adev)
{
	/* Some of the registers might be dependent on GRBM_GFX_INDEX */
	mutex_lock(&adev->grbm_idx_mutex);

	if (amdgpu_sriov_vf(adev)) {
		xgpu_vi_init_golden_registers(adev);
		mutex_unlock(&adev->grbm_idx_mutex);
		return;
	}

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		amdgpu_device_program_register_sequence(adev,
							iceland_mgcg_cgcg_init,
							ARRAY_SIZE(iceland_mgcg_cgcg_init));
		break;
	case CHIP_FIJI:
		amdgpu_device_program_register_sequence(adev,
							fiji_mgcg_cgcg_init,
							ARRAY_SIZE(fiji_mgcg_cgcg_init));
		break;
	case CHIP_TONGA:
		amdgpu_device_program_register_sequence(adev,
							tonga_mgcg_cgcg_init,
							ARRAY_SIZE(tonga_mgcg_cgcg_init));
		break;
	case CHIP_CARRIZO:
		amdgpu_device_program_register_sequence(adev,
							cz_mgcg_cgcg_init,
							ARRAY_SIZE(cz_mgcg_cgcg_init));
		break;
	case CHIP_STONEY:
		amdgpu_device_program_register_sequence(adev,
							stoney_mgcg_cgcg_init,
							ARRAY_SIZE(stoney_mgcg_cgcg_init));
		break;
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
	default:
		break;
	}
	mutex_unlock(&adev->grbm_idx_mutex);
}