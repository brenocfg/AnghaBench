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
struct smu_context {int od_enabled; } ;
struct TYPE_2__ {int pp_feature; } ;
struct amdgpu_device {int asic_type; TYPE_1__ pm; struct smu_context smu; } ;

/* Variables and functions */
#define  CHIP_ARCTURUS 133 
#define  CHIP_NAVI10 132 
#define  CHIP_NAVI12 131 
#define  CHIP_NAVI14 130 
#define  CHIP_RENOIR 129 
#define  CHIP_VEGA20 128 
 int EINVAL ; 
 int PP_OVERDRIVE_MASK ; 
 int /*<<< orphan*/  smu_v11_0_set_smu_funcs (struct smu_context*) ; 
 int /*<<< orphan*/  smu_v12_0_set_smu_funcs (struct smu_context*) ; 

__attribute__((used)) static int smu_set_funcs(struct amdgpu_device *adev)
{
	struct smu_context *smu = &adev->smu;

	switch (adev->asic_type) {
	case CHIP_VEGA20:
	case CHIP_NAVI10:
	case CHIP_NAVI14:
	case CHIP_NAVI12:
	case CHIP_ARCTURUS:
		if (adev->pm.pp_feature & PP_OVERDRIVE_MASK)
			smu->od_enabled = true;
		smu_v11_0_set_smu_funcs(smu);
		break;
	case CHIP_RENOIR:
		if (adev->pm.pp_feature & PP_OVERDRIVE_MASK)
			smu->od_enabled = true;
		smu_v12_0_set_smu_funcs(smu);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}