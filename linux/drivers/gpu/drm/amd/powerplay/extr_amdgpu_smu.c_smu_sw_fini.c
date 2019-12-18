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
struct smu_context {int /*<<< orphan*/ * irq_source; } ;
struct amdgpu_device {struct smu_context smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int smu_fini_power (struct smu_context*) ; 
 int smu_smc_table_sw_fini (struct smu_context*) ; 

__attribute__((used)) static int smu_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct smu_context *smu = &adev->smu;
	int ret;

	kfree(smu->irq_source);
	smu->irq_source = NULL;

	ret = smu_smc_table_sw_fini(smu);
	if (ret) {
		pr_err("Failed to sw fini smc table!\n");
		return ret;
	}

	ret = smu_fini_power(smu);
	if (ret) {
		pr_err("Failed to init smu_fini_power!\n");
		return ret;
	}

	return 0;
}