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
#define  CHIP_RENOIR 128 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  renoir_set_ppt_funcs (struct smu_context*) ; 
 int /*<<< orphan*/  smu_v12_0_funcs ; 

void smu_v12_0_set_smu_funcs(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;

	smu->funcs = &smu_v12_0_funcs;

	switch (adev->asic_type) {
	case CHIP_RENOIR:
		renoir_set_ppt_funcs(smu);
		break;
	default:
		pr_warn("Unknown asic for smu12\n");
	}
}