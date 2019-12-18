#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smu_context {int /*<<< orphan*/  mutex; struct amdgpu_device* adev; } ;
struct TYPE_2__ {int pp_feature; } ;
struct amdgpu_device {int asic_type; TYPE_1__ pm; } ;

/* Variables and functions */
#define  CHIP_NAVI10 131 
#define  CHIP_NAVI12 130 
#define  CHIP_NAVI14 129 
#define  CHIP_VEGA20 128 
 int PP_GFXOFF_MASK ; 
 int /*<<< orphan*/  SMU_MSG_AllowGfxOff ; 
 int /*<<< orphan*/  SMU_MSG_DisallowGfxOff ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_send_smc_msg (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v11_0_gfx_off_control(struct smu_context *smu, bool enable)
{
	int ret = 0;
	struct amdgpu_device *adev = smu->adev;

	switch (adev->asic_type) {
	case CHIP_VEGA20:
		break;
	case CHIP_NAVI10:
	case CHIP_NAVI14:
	case CHIP_NAVI12:
		if (!(adev->pm.pp_feature & PP_GFXOFF_MASK))
			return 0;
		mutex_lock(&smu->mutex);
		if (enable)
			ret = smu_send_smc_msg(smu, SMU_MSG_AllowGfxOff);
		else
			ret = smu_send_smc_msg(smu, SMU_MSG_DisallowGfxOff);
		mutex_unlock(&smu->mutex);
		break;
	default:
		break;
	}

	return ret;
}