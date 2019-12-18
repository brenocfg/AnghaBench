#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_vm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  status_lock; int /*<<< orphan*/  freed; int /*<<< orphan*/  va; } ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ last; scalar_t__ start; } ;
struct radeon_bo_va {int /*<<< orphan*/  last_pt_update; int /*<<< orphan*/  vm_status; int /*<<< orphan*/  bo; TYPE_1__ it; int /*<<< orphan*/  bo_list; struct radeon_vm* vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  interval_tree_remove (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct radeon_bo_va*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_fence_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void radeon_vm_bo_rmv(struct radeon_device *rdev,
		      struct radeon_bo_va *bo_va)
{
	struct radeon_vm *vm = bo_va->vm;

	list_del(&bo_va->bo_list);

	mutex_lock(&vm->mutex);
	if (bo_va->it.start || bo_va->it.last)
		interval_tree_remove(&bo_va->it, &vm->va);

	spin_lock(&vm->status_lock);
	list_del(&bo_va->vm_status);
	if (bo_va->it.start || bo_va->it.last) {
		bo_va->bo = radeon_bo_ref(bo_va->bo);
		list_add(&bo_va->vm_status, &vm->freed);
	} else {
		radeon_fence_unref(&bo_va->last_pt_update);
		kfree(bo_va);
	}
	spin_unlock(&vm->status_lock);

	mutex_unlock(&vm->mutex);
}