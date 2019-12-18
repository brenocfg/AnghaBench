#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int placement; } ;
struct ttm_buffer_object {TYPE_8__ mem; } ;
struct amdgpu_vm_bo_base {struct amdgpu_vm* vm; struct amdgpu_vm_bo_base* next; } ;
struct TYPE_14__ {TYPE_5__* bo; } ;
struct TYPE_15__ {TYPE_6__ base; } ;
struct amdgpu_vm {int bulk_moveable; TYPE_7__ root; } ;
struct TYPE_9__ {scalar_t__ resv; } ;
struct TYPE_10__ {TYPE_1__ base; } ;
struct amdgpu_bo {TYPE_2__ tbo; struct amdgpu_vm_bo_base* vm_bo; int /*<<< orphan*/  parent; } ;
struct TYPE_11__ {scalar_t__ resv; } ;
struct TYPE_12__ {TYPE_3__ base; } ;
struct TYPE_13__ {TYPE_4__ tbo; } ;

/* Variables and functions */
 int TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  amdgpu_bo_is_amdgpu_bo (struct ttm_buffer_object*) ; 
 struct amdgpu_bo* ttm_to_amdgpu_bo (struct ttm_buffer_object*) ; 

void amdgpu_vm_del_from_lru_notify(struct ttm_buffer_object *bo)
{
	struct amdgpu_bo *abo;
	struct amdgpu_vm_bo_base *bo_base;

	if (!amdgpu_bo_is_amdgpu_bo(bo))
		return;

	if (bo->mem.placement & TTM_PL_FLAG_NO_EVICT)
		return;

	abo = ttm_to_amdgpu_bo(bo);
	if (!abo->parent)
		return;
	for (bo_base = abo->vm_bo; bo_base; bo_base = bo_base->next) {
		struct amdgpu_vm *vm = bo_base->vm;

		if (abo->tbo.base.resv == vm->root.base.bo->tbo.base.resv)
			vm->bulk_moveable = false;
	}

}