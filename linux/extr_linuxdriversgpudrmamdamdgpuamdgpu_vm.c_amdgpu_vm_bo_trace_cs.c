#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ww_acquire_ctx {int dummy; } ;
struct amdgpu_vm {int /*<<< orphan*/  va; } ;
struct amdgpu_bo_va_mapping {TYPE_4__* bo_va; } ;
struct TYPE_8__ {TYPE_2__* resv; } ;
struct amdgpu_bo {TYPE_3__ tbo; } ;
struct TYPE_10__ {struct amdgpu_bo* bo; } ;
struct TYPE_9__ {TYPE_5__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_7__ {TYPE_1__ lock; } ;

/* Variables and functions */
 struct ww_acquire_ctx* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_MAX ; 
 struct amdgpu_bo_va_mapping* amdgpu_vm_it_iter_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amdgpu_bo_va_mapping* amdgpu_vm_it_iter_next (struct amdgpu_bo_va_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_amdgpu_vm_bo_cs (struct amdgpu_bo_va_mapping*) ; 
 int /*<<< orphan*/  trace_amdgpu_vm_bo_cs_enabled () ; 

void amdgpu_vm_bo_trace_cs(struct amdgpu_vm *vm, struct ww_acquire_ctx *ticket)
{
	struct amdgpu_bo_va_mapping *mapping;

	if (!trace_amdgpu_vm_bo_cs_enabled())
		return;

	for (mapping = amdgpu_vm_it_iter_first(&vm->va, 0, U64_MAX); mapping;
	     mapping = amdgpu_vm_it_iter_next(mapping, 0, U64_MAX)) {
		if (mapping->bo_va && mapping->bo_va->base.bo) {
			struct amdgpu_bo *bo;

			bo = mapping->bo_va->base.bo;
			if (READ_ONCE(bo->tbo.resv->lock.ctx) != ticket)
				continue;
		}

		trace_amdgpu_vm_bo_cs(mapping);
	}
}