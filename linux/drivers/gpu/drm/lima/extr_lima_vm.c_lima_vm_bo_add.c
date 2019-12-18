#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lima_vm {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ start; } ;
struct lima_bo_va {int ref_count; TYPE_2__ node; int /*<<< orphan*/  list; struct lima_vm* vm; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct lima_bo {int /*<<< orphan*/  lock; int /*<<< orphan*/  va; int /*<<< orphan*/  pages_dma_addr; TYPE_1__ gem; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drm_mm_insert_node (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_remove_node (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct lima_bo_va*) ; 
 struct lima_bo_va* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct lima_bo_va* lima_vm_bo_find (struct lima_vm*,struct lima_bo*) ; 
 int lima_vm_map_page_table (struct lima_vm*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int lima_vm_bo_add(struct lima_vm *vm, struct lima_bo *bo, bool create)
{
	struct lima_bo_va *bo_va;
	int err;

	mutex_lock(&bo->lock);

	bo_va = lima_vm_bo_find(vm, bo);
	if (bo_va) {
		bo_va->ref_count++;
		mutex_unlock(&bo->lock);
		return 0;
	}

	/* should not create new bo_va if not asked by caller */
	if (!create) {
		mutex_unlock(&bo->lock);
		return -ENOENT;
	}

	bo_va = kzalloc(sizeof(*bo_va), GFP_KERNEL);
	if (!bo_va) {
		err = -ENOMEM;
		goto err_out0;
	}

	bo_va->vm = vm;
	bo_va->ref_count = 1;

	mutex_lock(&vm->lock);

	err = drm_mm_insert_node(&vm->mm, &bo_va->node, bo->gem.size);
	if (err)
		goto err_out1;

	err = lima_vm_map_page_table(vm, bo->pages_dma_addr, bo_va->node.start,
				     bo_va->node.start + bo_va->node.size - 1);
	if (err)
		goto err_out2;

	mutex_unlock(&vm->lock);

	list_add_tail(&bo_va->list, &bo->va);

	mutex_unlock(&bo->lock);
	return 0;

err_out2:
	drm_mm_remove_node(&bo_va->node);
err_out1:
	mutex_unlock(&vm->lock);
	kfree(bo_va);
err_out0:
	mutex_unlock(&bo->lock);
	return err;
}