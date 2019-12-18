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
struct smu_context {int /*<<< orphan*/ * funcs; struct amdgpu_device* adev; } ;
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
#define  CHIP_ARCTURUS 132 
#define  CHIP_NAVI10 131 
#define  CHIP_NAVI12 130 
#define  CHIP_NAVI14 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  arcturus_set_ppt_funcs (struct smu_context*) ; 
 int /*<<< orphan*/  navi10_set_ppt_funcs (struct smu_context*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  smu_v11_0_funcs ; 
 int /*<<< orphan*/  vega20_set_ppt_funcs (struct smu_context*) ; 

void smu_v11_0_set_smu_funcs(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;

	smu->funcs = &smu_v11_0_funcs;
	switch (adev->asic_type) {
	case CHIP_VEGA20:
		vega20_set_ppt_funcs(smu);
		break;
	case CHIP_ARCTURUS:
		arcturus_set_ppt_funcs(smu);
		break;
	case CHIP_NAVI10:
	case CHIP_NAVI14:
	case CHIP_NAVI12:
		navi10_set_ppt_funcs(smu);
		break;
	default:
		pr_warn("Unknown asic for smu11\n");
	}
}