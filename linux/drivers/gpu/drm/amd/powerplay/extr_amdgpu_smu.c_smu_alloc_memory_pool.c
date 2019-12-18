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
typedef  int uint64_t ;
struct smu_table {int size; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  mc_address; int /*<<< orphan*/  bo; int /*<<< orphan*/  domain; int /*<<< orphan*/  align; } ;
struct smu_table_context {struct smu_table memory_pool; } ;
struct smu_context {int pool_size; struct smu_table_context smu_table; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  SMU_MEMORY_POOL_SIZE_1_GB 131 
#define  SMU_MEMORY_POOL_SIZE_256_MB 130 
#define  SMU_MEMORY_POOL_SIZE_2_GB 129 
#define  SMU_MEMORY_POOL_SIZE_512_MB 128 
 int SMU_MEMORY_POOL_SIZE_ZERO ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smu_alloc_memory_pool(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	struct smu_table_context *smu_table = &smu->smu_table;
	struct smu_table *memory_pool = &smu_table->memory_pool;
	uint64_t pool_size = smu->pool_size;
	int ret = 0;

	if (pool_size == SMU_MEMORY_POOL_SIZE_ZERO)
		return ret;

	memory_pool->size = pool_size;
	memory_pool->align = PAGE_SIZE;
	memory_pool->domain = AMDGPU_GEM_DOMAIN_GTT;

	switch (pool_size) {
	case SMU_MEMORY_POOL_SIZE_256_MB:
	case SMU_MEMORY_POOL_SIZE_512_MB:
	case SMU_MEMORY_POOL_SIZE_1_GB:
	case SMU_MEMORY_POOL_SIZE_2_GB:
		ret = amdgpu_bo_create_kernel(adev,
					      memory_pool->size,
					      memory_pool->align,
					      memory_pool->domain,
					      &memory_pool->bo,
					      &memory_pool->mc_address,
					      &memory_pool->cpu_addr);
		break;
	default:
		break;
	}

	return ret;
}