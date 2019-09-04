#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_vm_bo_base {int moved; int /*<<< orphan*/  vm_status; int /*<<< orphan*/  bo_list; struct amdgpu_bo* bo; struct amdgpu_vm* vm; } ;
struct TYPE_9__ {TYPE_2__* bo; } ;
struct TYPE_10__ {TYPE_3__ base; } ;
struct amdgpu_vm {int /*<<< orphan*/  evicted; TYPE_4__ root; int /*<<< orphan*/  relocated; } ;
struct TYPE_11__ {int /*<<< orphan*/  mem_type; } ;
struct TYPE_12__ {scalar_t__ type; scalar_t__ resv; TYPE_5__ mem; } ;
struct amdgpu_bo {int preferred_domains; TYPE_6__ tbo; int /*<<< orphan*/  va; } ;
struct TYPE_7__ {scalar_t__ resv; } ;
struct TYPE_8__ {TYPE_1__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int amdgpu_mem_type_to_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ttm_bo_type_kernel ; 

__attribute__((used)) static void amdgpu_vm_bo_base_init(struct amdgpu_vm_bo_base *base,
				   struct amdgpu_vm *vm,
				   struct amdgpu_bo *bo)
{
	base->vm = vm;
	base->bo = bo;
	INIT_LIST_HEAD(&base->bo_list);
	INIT_LIST_HEAD(&base->vm_status);

	if (!bo)
		return;
	list_add_tail(&base->bo_list, &bo->va);

	if (bo->tbo.type == ttm_bo_type_kernel)
		list_move(&base->vm_status, &vm->relocated);

	if (bo->tbo.resv != vm->root.base.bo->tbo.resv)
		return;

	if (bo->preferred_domains &
	    amdgpu_mem_type_to_domain(bo->tbo.mem.mem_type))
		return;

	/*
	 * we checked all the prerequisites, but it looks like this per vm bo
	 * is currently evicted. add the bo to the evicted list to make sure it
	 * is validated on next vm use to avoid fault.
	 * */
	list_move_tail(&base->vm_status, &vm->evicted);
	base->moved = true;
}