#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int flags; TYPE_2__* vma; } ;
struct TYPE_6__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {int /*<<< orphan*/ * moving; TYPE_3__ base; } ;
struct TYPE_5__ {TYPE_1__* vm_mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int FAULT_FLAG_ALLOW_RETRY ; 
 int FAULT_FLAG_RETRY_NOWAIT ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  VM_FAULT_RETRY ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 scalar_t__ dma_fence_is_signaled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int dma_fence_wait (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_resv_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ttm_bo_get (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_put (struct ttm_buffer_object*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_fault_t ttm_bo_vm_fault_idle(struct ttm_buffer_object *bo,
				struct vm_fault *vmf)
{
	vm_fault_t ret = 0;
	int err = 0;

	if (likely(!bo->moving))
		goto out_unlock;

	/*
	 * Quick non-stalling check for idle.
	 */
	if (dma_fence_is_signaled(bo->moving))
		goto out_clear;

	/*
	 * If possible, avoid waiting for GPU with mmap_sem
	 * held.
	 */
	if (vmf->flags & FAULT_FLAG_ALLOW_RETRY) {
		ret = VM_FAULT_RETRY;
		if (vmf->flags & FAULT_FLAG_RETRY_NOWAIT)
			goto out_unlock;

		ttm_bo_get(bo);
		up_read(&vmf->vma->vm_mm->mmap_sem);
		(void) dma_fence_wait(bo->moving, true);
		dma_resv_unlock(bo->base.resv);
		ttm_bo_put(bo);
		goto out_unlock;
	}

	/*
	 * Ordinary wait.
	 */
	err = dma_fence_wait(bo->moving, true);
	if (unlikely(err != 0)) {
		ret = (err != -ERESTARTSYS) ? VM_FAULT_SIGBUS :
			VM_FAULT_NOPAGE;
		goto out_unlock;
	}

out_clear:
	dma_fence_put(bo->moving);
	bo->moving = NULL;

out_unlock:
	return ret;
}