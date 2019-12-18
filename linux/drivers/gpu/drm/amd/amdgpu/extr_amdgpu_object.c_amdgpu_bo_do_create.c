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
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; int /*<<< orphan*/  bytes_moved; int /*<<< orphan*/  flags; int /*<<< orphan*/  resv; } ;
struct dma_fence {int dummy; } ;
struct TYPE_10__ {scalar_t__ visible_vram_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {TYPE_5__ gmc; TYPE_1__ mman; int /*<<< orphan*/  ddev; } ;
struct amdgpu_bo_param {unsigned long size; int domain; unsigned long byte_align; int preferred_domain; int flags; int /*<<< orphan*/  resv; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  resv; } ;
struct TYPE_7__ {scalar_t__ mem_type; scalar_t__ start; int placement; } ;
struct TYPE_8__ {int priority; TYPE_4__ base; struct dma_fence* moving; TYPE_2__ mem; int /*<<< orphan*/ * bdev; } ;
struct amdgpu_bo {int preferred_domains; int allowed_domains; int flags; TYPE_3__ tbo; int /*<<< orphan*/  placement; int /*<<< orphan*/ * vm_bo; int /*<<< orphan*/  shadow_list; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int) ; 
 int AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int AMDGPU_GEM_CREATE_CPU_GTT_USWC ; 
 int AMDGPU_GEM_CREATE_VRAM_CLEARED ; 
 int AMDGPU_GEM_DOMAIN_CPU ; 
 int AMDGPU_GEM_DOMAIN_GDS ; 
 int AMDGPU_GEM_DOMAIN_GTT ; 
 int AMDGPU_GEM_DOMAIN_GWS ; 
 int AMDGPU_GEM_DOMAIN_OA ; 
 int AMDGPU_GEM_DOMAIN_VRAM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TTM_OPT_FLAG_ALLOW_RES_EVICT ; 
 int TTM_PL_FLAG_VRAM ; 
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  amdgpu_bo_destroy ; 
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,struct dma_fence*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_support_uswc (int) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_validate_size (struct amdgpu_device*,unsigned long,int) ; 
 int /*<<< orphan*/  amdgpu_cs_report_moved_bytes (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_fill_buffer (struct amdgpu_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  amdgpu_gmc_vram_full_visible (TYPE_5__*) ; 
 struct dma_fence* dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_resv_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_private_object_init (int /*<<< orphan*/ ,TYPE_4__*,unsigned long) ; 
 struct amdgpu_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_amdgpu_bo_create (struct amdgpu_bo*) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,unsigned long,int) ; 
 int ttm_bo_init_reserved (int /*<<< orphan*/ *,TYPE_3__*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,struct ttm_operation_ctx*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int amdgpu_bo_do_create(struct amdgpu_device *adev,
			       struct amdgpu_bo_param *bp,
			       struct amdgpu_bo **bo_ptr)
{
	struct ttm_operation_ctx ctx = {
		.interruptible = (bp->type != ttm_bo_type_kernel),
		.no_wait_gpu = false,
		.resv = bp->resv,
		.flags = bp->type != ttm_bo_type_kernel ?
			TTM_OPT_FLAG_ALLOW_RES_EVICT : 0
	};
	struct amdgpu_bo *bo;
	unsigned long page_align, size = bp->size;
	size_t acc_size;
	int r;

	/* Note that GDS/GWS/OA allocates 1 page per byte/resource. */
	if (bp->domain & (AMDGPU_GEM_DOMAIN_GWS | AMDGPU_GEM_DOMAIN_OA)) {
		/* GWS and OA don't need any alignment. */
		page_align = bp->byte_align;
		size <<= PAGE_SHIFT;
	} else if (bp->domain & AMDGPU_GEM_DOMAIN_GDS) {
		/* Both size and alignment must be a multiple of 4. */
		page_align = ALIGN(bp->byte_align, 4);
		size = ALIGN(size, 4) << PAGE_SHIFT;
	} else {
		/* Memory should be aligned at least to a page size. */
		page_align = ALIGN(bp->byte_align, PAGE_SIZE) >> PAGE_SHIFT;
		size = ALIGN(size, PAGE_SIZE);
	}

	if (!amdgpu_bo_validate_size(adev, size, bp->domain))
		return -ENOMEM;

	*bo_ptr = NULL;

	acc_size = ttm_bo_dma_acc_size(&adev->mman.bdev, size,
				       sizeof(struct amdgpu_bo));

	bo = kzalloc(sizeof(struct amdgpu_bo), GFP_KERNEL);
	if (bo == NULL)
		return -ENOMEM;
	drm_gem_private_object_init(adev->ddev, &bo->tbo.base, size);
	INIT_LIST_HEAD(&bo->shadow_list);
	bo->vm_bo = NULL;
	bo->preferred_domains = bp->preferred_domain ? bp->preferred_domain :
		bp->domain;
	bo->allowed_domains = bo->preferred_domains;
	if (bp->type != ttm_bo_type_kernel &&
	    bo->allowed_domains == AMDGPU_GEM_DOMAIN_VRAM)
		bo->allowed_domains |= AMDGPU_GEM_DOMAIN_GTT;

	bo->flags = bp->flags;

	if (!amdgpu_bo_support_uswc(bo->flags))
		bo->flags &= ~AMDGPU_GEM_CREATE_CPU_GTT_USWC;

	bo->tbo.bdev = &adev->mman.bdev;
	if (bp->domain & (AMDGPU_GEM_DOMAIN_GWS | AMDGPU_GEM_DOMAIN_OA |
			  AMDGPU_GEM_DOMAIN_GDS))
		amdgpu_bo_placement_from_domain(bo, AMDGPU_GEM_DOMAIN_CPU);
	else
		amdgpu_bo_placement_from_domain(bo, bp->domain);
	if (bp->type == ttm_bo_type_kernel)
		bo->tbo.priority = 1;

	r = ttm_bo_init_reserved(&adev->mman.bdev, &bo->tbo, size, bp->type,
				 &bo->placement, page_align, &ctx, acc_size,
				 NULL, bp->resv, &amdgpu_bo_destroy);
	if (unlikely(r != 0))
		return r;

	if (!amdgpu_gmc_vram_full_visible(&adev->gmc) &&
	    bo->tbo.mem.mem_type == TTM_PL_VRAM &&
	    bo->tbo.mem.start < adev->gmc.visible_vram_size >> PAGE_SHIFT)
		amdgpu_cs_report_moved_bytes(adev, ctx.bytes_moved,
					     ctx.bytes_moved);
	else
		amdgpu_cs_report_moved_bytes(adev, ctx.bytes_moved, 0);

	if (bp->flags & AMDGPU_GEM_CREATE_VRAM_CLEARED &&
	    bo->tbo.mem.placement & TTM_PL_FLAG_VRAM) {
		struct dma_fence *fence;

		r = amdgpu_fill_buffer(bo, 0, bo->tbo.base.resv, &fence);
		if (unlikely(r))
			goto fail_unreserve;

		amdgpu_bo_fence(bo, fence, false);
		dma_fence_put(bo->tbo.moving);
		bo->tbo.moving = dma_fence_get(fence);
		dma_fence_put(fence);
	}
	if (!bp->resv)
		amdgpu_bo_unreserve(bo);
	*bo_ptr = bo;

	trace_amdgpu_bo_create(bo);

	/* Treat CPU_ACCESS_REQUIRED only as a hint if given by UMD */
	if (bp->type == ttm_bo_type_device)
		bo->flags &= ~AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;

	return 0;

fail_unreserve:
	if (!bp->resv)
		dma_resv_unlock(bo->tbo.base.resv);
	amdgpu_bo_unref(&bo);
	return r;
}