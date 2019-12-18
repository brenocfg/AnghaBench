#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_fpriv {struct amdgpu_vm vm; } ;
struct amdgpu_cs_parser {int /*<<< orphan*/  ticket; TYPE_1__* filp; } ;
struct amdgpu_bo_va_mapping {TYPE_3__* bo_va; } ;
struct TYPE_10__ {int /*<<< orphan*/  resv; } ;
struct TYPE_11__ {TYPE_4__ base; } ;
struct amdgpu_bo {int flags; TYPE_5__ tbo; int /*<<< orphan*/  placement; int /*<<< orphan*/  allowed_domains; } ;
struct TYPE_8__ {struct amdgpu_bo* bo; } ;
struct TYPE_9__ {TYPE_2__ base; } ;
struct TYPE_7__ {struct amdgpu_fpriv* driver_priv; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS ; 
 int /*<<< orphan*/  AMDGPU_GPU_PAGE_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 int amdgpu_ttm_alloc_gart (TYPE_5__*) ; 
 struct amdgpu_bo_va_mapping* amdgpu_vm_bo_lookup_mapping (struct amdgpu_vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_resv_locking_ctx (int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (TYPE_5__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 

int amdgpu_cs_find_mapping(struct amdgpu_cs_parser *parser,
			   uint64_t addr, struct amdgpu_bo **bo,
			   struct amdgpu_bo_va_mapping **map)
{
	struct amdgpu_fpriv *fpriv = parser->filp->driver_priv;
	struct ttm_operation_ctx ctx = { false, false };
	struct amdgpu_vm *vm = &fpriv->vm;
	struct amdgpu_bo_va_mapping *mapping;
	int r;

	addr /= AMDGPU_GPU_PAGE_SIZE;

	mapping = amdgpu_vm_bo_lookup_mapping(vm, addr);
	if (!mapping || !mapping->bo_va || !mapping->bo_va->base.bo)
		return -EINVAL;

	*bo = mapping->bo_va->base.bo;
	*map = mapping;

	/* Double check that the BO is reserved by this CS */
	if (dma_resv_locking_ctx((*bo)->tbo.base.resv) != &parser->ticket)
		return -EINVAL;

	if (!((*bo)->flags & AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS)) {
		(*bo)->flags |= AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
		amdgpu_bo_placement_from_domain(*bo, (*bo)->allowed_domains);
		r = ttm_bo_validate(&(*bo)->tbo, &(*bo)->placement, &ctx);
		if (r)
			return r;
	}

	return amdgpu_ttm_alloc_gart(&(*bo)->tbo);
}