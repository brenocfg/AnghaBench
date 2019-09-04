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
struct amdgpu_bo {int dummy; } ;
struct amdgpu_amdkfd_fence {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_amdkfd_fence**) ; 

__attribute__((used)) static void amdgpu_amdkfd_add_eviction_fence(struct amdgpu_bo *bo,
				struct amdgpu_amdkfd_fence **ef_list,
				unsigned int ef_count)
{
	int i;

	if (!ef_list || !ef_count)
		return;

	for (i = 0; i < ef_count; i++) {
		amdgpu_bo_fence(bo, &ef_list[i]->base, true);
		/* Re-adding the fence takes an additional reference. Drop that
		 * reference.
		 */
		dma_fence_put(&ef_list[i]->base);
	}

	kfree(ef_list);
}