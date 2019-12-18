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
typedef  scalar_t__ uint32_t ;
struct smu_table_context {scalar_t__ table_count; struct smu_table* tables; } ;
struct smu_table {scalar_t__ size; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  mc_address; int /*<<< orphan*/  bo; int /*<<< orphan*/  domain; int /*<<< orphan*/  align; } ;
struct smu_context {struct smu_table_context smu_table; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smu_init_fb_allocations(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	struct smu_table_context *smu_table = &smu->smu_table;
	struct smu_table *tables = smu_table->tables;
	uint32_t table_count = smu_table->table_count;
	uint32_t i = 0;
	int32_t ret = 0;

	if (table_count <= 0)
		return -EINVAL;

	for (i = 0 ; i < table_count; i++) {
		if (tables[i].size == 0)
			continue;
		ret = amdgpu_bo_create_kernel(adev,
					      tables[i].size,
					      tables[i].align,
					      tables[i].domain,
					      &tables[i].bo,
					      &tables[i].mc_address,
					      &tables[i].cpu_addr);
		if (ret)
			goto failed;
	}

	return 0;
failed:
	for (; i > 0; i--) {
		if (tables[i].size == 0)
			continue;
		amdgpu_bo_free_kernel(&tables[i].bo,
				      &tables[i].mc_address,
				      &tables[i].cpu_addr);

	}
	return ret;
}