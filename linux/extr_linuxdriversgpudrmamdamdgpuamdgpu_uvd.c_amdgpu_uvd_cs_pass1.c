#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct amdgpu_uvd_cs_ctx {int /*<<< orphan*/  idx; int /*<<< orphan*/  ib_idx; TYPE_3__* parser; } ;
struct amdgpu_bo_va_mapping {int dummy; } ;
struct amdgpu_bo {int /*<<< orphan*/  placement; int /*<<< orphan*/  tbo; } ;
struct TYPE_7__ {TYPE_2__* adev; } ;
struct TYPE_5__ {int /*<<< orphan*/  address_64_bit; } ;
struct TYPE_6__ {TYPE_1__ uvd; } ;

/* Variables and functions */
 int AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,int) ; 
 int amdgpu_cs_find_mapping (TYPE_3__*,int /*<<< orphan*/ ,struct amdgpu_bo**,struct amdgpu_bo_va_mapping**) ; 
 int amdgpu_get_ib_value (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_uvd_force_into_uvd_segment (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_uvd_get_addr_from_ctx (struct amdgpu_uvd_cs_ctx*) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 

__attribute__((used)) static int amdgpu_uvd_cs_pass1(struct amdgpu_uvd_cs_ctx *ctx)
{
	struct ttm_operation_ctx tctx = { false, false };
	struct amdgpu_bo_va_mapping *mapping;
	struct amdgpu_bo *bo;
	uint32_t cmd;
	uint64_t addr = amdgpu_uvd_get_addr_from_ctx(ctx);
	int r = 0;

	r = amdgpu_cs_find_mapping(ctx->parser, addr, &bo, &mapping);
	if (r) {
		DRM_ERROR("Can't find BO for addr 0x%08Lx\n", addr);
		return r;
	}

	if (!ctx->parser->adev->uvd.address_64_bit) {
		/* check if it's a message or feedback command */
		cmd = amdgpu_get_ib_value(ctx->parser, ctx->ib_idx, ctx->idx) >> 1;
		if (cmd == 0x0 || cmd == 0x3) {
			/* yes, force it into VRAM */
			uint32_t domain = AMDGPU_GEM_DOMAIN_VRAM;
			amdgpu_bo_placement_from_domain(bo, domain);
		}
		amdgpu_uvd_force_into_uvd_segment(bo);

		r = ttm_bo_validate(&bo->tbo, &bo->placement, &tctx);
	}

	return r;
}