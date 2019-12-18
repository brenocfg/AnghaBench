#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_vm_bo_base {int moved; struct amdgpu_vm* vm; struct amdgpu_vm_bo_base* next; } ;
struct TYPE_13__ {TYPE_5__* bo; } ;
struct TYPE_14__ {TYPE_6__ base; } ;
struct amdgpu_vm {TYPE_7__ root; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_8__ {scalar_t__ resv; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ base; } ;
struct amdgpu_bo {TYPE_2__ tbo; struct amdgpu_vm_bo_base* vm_bo; struct amdgpu_bo* parent; struct amdgpu_bo* shadow; } ;
struct TYPE_10__ {scalar_t__ resv; } ;
struct TYPE_11__ {TYPE_3__ base; } ;
struct TYPE_12__ {TYPE_4__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_vm_bo_evicted (struct amdgpu_vm_bo_base*) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_invalidated (struct amdgpu_vm_bo_base*) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_moved (struct amdgpu_vm_bo_base*) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_relocated (struct amdgpu_vm_bo_base*) ; 
 scalar_t__ ttm_bo_type_kernel ; 

void amdgpu_vm_bo_invalidate(struct amdgpu_device *adev,
			     struct amdgpu_bo *bo, bool evicted)
{
	struct amdgpu_vm_bo_base *bo_base;

	/* shadow bo doesn't have bo base, its validation needs its parent */
	if (bo->parent && bo->parent->shadow == bo)
		bo = bo->parent;

	for (bo_base = bo->vm_bo; bo_base; bo_base = bo_base->next) {
		struct amdgpu_vm *vm = bo_base->vm;

		if (evicted && bo->tbo.base.resv == vm->root.base.bo->tbo.base.resv) {
			amdgpu_vm_bo_evicted(bo_base);
			continue;
		}

		if (bo_base->moved)
			continue;
		bo_base->moved = true;

		if (bo->tbo.type == ttm_bo_type_kernel)
			amdgpu_vm_bo_relocated(bo_base);
		else if (bo->tbo.base.resv == vm->root.base.bo->tbo.base.resv)
			amdgpu_vm_bo_moved(bo_base);
		else
			amdgpu_vm_bo_invalidated(bo_base);
	}
}