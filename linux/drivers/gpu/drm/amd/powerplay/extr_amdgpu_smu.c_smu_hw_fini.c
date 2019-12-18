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
struct smu_table_context {int /*<<< orphan*/ * overdrive_table; int /*<<< orphan*/ * max_sustainable_clocks; int /*<<< orphan*/ * driver_pptable; } ;
struct smu_context {struct smu_table_context smu_table; } ;
struct amdgpu_device {int flags; struct smu_context smu; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int smu_fini_fb_allocations (struct smu_context*) ; 
 int smu_free_memory_pool (struct smu_context*) ; 
 int /*<<< orphan*/  smu_powergate_sdma (struct smu_context*,int) ; 
 int /*<<< orphan*/  smu_powergate_vcn (struct smu_context*,int) ; 

__attribute__((used)) static int smu_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct smu_context *smu = &adev->smu;
	struct smu_table_context *table_context = &smu->smu_table;
	int ret = 0;

	if (adev->flags & AMD_IS_APU) {
		smu_powergate_sdma(&adev->smu, true);
		smu_powergate_vcn(&adev->smu, true);
	}

	kfree(table_context->driver_pptable);
	table_context->driver_pptable = NULL;

	kfree(table_context->max_sustainable_clocks);
	table_context->max_sustainable_clocks = NULL;

	kfree(table_context->overdrive_table);
	table_context->overdrive_table = NULL;

	ret = smu_fini_fb_allocations(smu);
	if (ret)
		return ret;

	ret = smu_free_memory_pool(smu);
	if (ret)
		return ret;

	return 0;
}