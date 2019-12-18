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
struct ttm_validate_buffer {int num_shared; int /*<<< orphan*/  head; int /*<<< orphan*/ * bo; } ;
struct kgd_mem {struct amdgpu_bo* bo; struct ttm_validate_buffer validate_list; } ;
struct amdkfd_process_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  kfd_bo_list; int /*<<< orphan*/  userptr_valid_list; } ;
struct amdgpu_bo {int /*<<< orphan*/  tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_kgd_mem_to_kfd_bo_list(struct kgd_mem *mem,
				struct amdkfd_process_info *process_info,
				bool userptr)
{
	struct ttm_validate_buffer *entry = &mem->validate_list;
	struct amdgpu_bo *bo = mem->bo;

	INIT_LIST_HEAD(&entry->head);
	entry->num_shared = 1;
	entry->bo = &bo->tbo;
	mutex_lock(&process_info->lock);
	if (userptr)
		list_add_tail(&entry->head, &process_info->userptr_valid_list);
	else
		list_add_tail(&entry->head, &process_info->kfd_bo_list);
	mutex_unlock(&process_info->lock);
}