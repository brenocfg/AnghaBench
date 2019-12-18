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
struct kgd_mem {int /*<<< orphan*/  lock; int /*<<< orphan*/  sync; struct amdgpu_bo* bo; } ;
struct amdkfd_process_info {int /*<<< orphan*/  eviction_fence; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_amdkfd_remove_eviction_fence (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_sync_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  remove_kgd_mem_from_kfd_bo_list (struct kgd_mem*,struct amdkfd_process_info*) ; 
 scalar_t__ unlikely (int) ; 

int amdgpu_amdkfd_remove_gws_from_process(void *info, void *mem)
{
	int ret;
	struct amdkfd_process_info *process_info = (struct amdkfd_process_info *)info;
	struct kgd_mem *kgd_mem = (struct kgd_mem *)mem;
	struct amdgpu_bo *gws_bo = kgd_mem->bo;

	/* Remove BO from process's validate list so restore worker won't touch
	 * it anymore
	 */
	remove_kgd_mem_from_kfd_bo_list(kgd_mem, process_info);

	ret = amdgpu_bo_reserve(gws_bo, false);
	if (unlikely(ret)) {
		pr_err("Reserve gws bo failed %d\n", ret);
		//TODO add BO back to validate_list?
		return ret;
	}
	amdgpu_amdkfd_remove_eviction_fence(gws_bo,
			process_info->eviction_fence);
	amdgpu_bo_unreserve(gws_bo);
	amdgpu_sync_free(&kgd_mem->sync);
	amdgpu_bo_unref(&gws_bo);
	mutex_destroy(&kgd_mem->lock);
	kfree(mem);
	return 0;
}