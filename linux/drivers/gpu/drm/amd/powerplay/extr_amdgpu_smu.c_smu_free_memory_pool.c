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
struct smu_table {scalar_t__ size; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  mc_address; int /*<<< orphan*/  bo; } ;
struct smu_table_context {struct smu_table memory_pool; } ;
struct smu_context {struct smu_table_context smu_table; } ;

/* Variables and functions */
 scalar_t__ SMU_MEMORY_POOL_SIZE_ZERO ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct smu_table*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu_free_memory_pool(struct smu_context *smu)
{
	struct smu_table_context *smu_table = &smu->smu_table;
	struct smu_table *memory_pool = &smu_table->memory_pool;
	int ret = 0;

	if (memory_pool->size == SMU_MEMORY_POOL_SIZE_ZERO)
		return ret;

	amdgpu_bo_free_kernel(&memory_pool->bo,
			      &memory_pool->mc_address,
			      &memory_pool->cpu_addr);

	memset(memory_pool, 0, sizeof(struct smu_table));

	return ret;
}