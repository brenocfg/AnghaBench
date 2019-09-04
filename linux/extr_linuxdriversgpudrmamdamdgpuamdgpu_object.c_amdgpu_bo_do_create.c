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
struct TYPE_9__ {scalar_t__ visible_vram_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {TYPE_4__ gmc; TYPE_1__ mman; int /*<<< orphan*/  ddev; } ;
struct amdgpu_bo_param {unsigned long size; int flags; int /*<<< orphan*/  resv; int /*<<< orphan*/  type; scalar_t__ domain; scalar_t__ preferred_domain; int /*<<< orphan*/  byte_align; } ;
struct TYPE_7__ {scalar_t__ mem_type; scalar_t__ start; int placement; } ;
struct TYPE_8__ {int priority; TYPE_5__* resv; struct dma_fence* moving; TYPE_2__ mem; int /*<<< orphan*/ * bdev; } ;
struct amdgpu_bo {int flags; TYPE_3__ tbo; int /*<<< orphan*/  placement; scalar_t__ allowed_domains; scalar_t__ preferred_domains; int /*<<< orphan*/  va; int /*<<< orphan*/  shadow_list; int /*<<< orphan*/  gem_base; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int AMDGPU_GEM_CREATE_CPU_GTT_USWC ; 
 int AMDGPU_GEM_CREATE_VRAM_CLEARED ; 
 scalar_t__ AMDGPU_GEM_DOMAIN_GTT ; 
 scalar_t__ AMDGPU_GEM_DOMAIN_VRAM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TTM_OPT_FLAG_ALLOW_RES_EVICT ; 
 int TTM_PL_FLAG_VRAM ; 
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  amdgpu_bo_destroy ; 
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,struct dma_fence*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_validate_size (struct amdgpu_device*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_cs_report_moved_bytes (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_fill_buffer (struct amdgpu_bo*,int /*<<< orphan*/ ,TYPE_5__*,struct dma_fence**) ; 
 int /*<<< orphan*/  amdgpu_gmc_vram_full_visible (TYPE_4__*) ; 
 struct dma_fence* dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  drm_arch_can_wc_memory () ; 
 int /*<<< orphan*/  drm_gem_private_object_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 struct amdgpu_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_amdgpu_bo_create (struct amdgpu_bo*) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,unsigned long,int) ; 
 int ttm_bo_init_reserved (int /*<<< orphan*/ *,TYPE_3__*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,struct ttm_operation_ctx*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  ww_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_bo_do_create(struct amdgpu_device *adev,
			       struct amdgpu_bo_param *bp,
			       struct amdgpu_bo **bo_ptr)
{
	struct ttm_operation_ctx ctx = {
		.interruptible = (bp->type != ttm_bo_type_kernel),
		.no_wait_gpu = false,
		.resv = bp->resv,
		.flags = TTM_OPT_FLAG_ALLOW_RES_EVICT
	};
	struct amdgpu_bo *bo;
	unsigned long page_align, size = bp->size;
	size_t acc_size;
	int r;

	page_align = roundup(bp->byte_align, PAGE_SIZE) >> PAGE_SHIFT;
	size = ALIGN(size, PAGE_SIZE);

	if (!amdgpu_bo_validate_size(adev, size, bp->domain))
		return -ENOMEM;

	*bo_ptr = NULL;

	acc_size = ttm_bo_dma_acc_size(&adev->mman.bdev, size,
				       sizeof(struct amdgpu_bo));

	bo = kzalloc(sizeof(struct amdgpu_bo), GFP_KERNEL);
	if (bo == NULL)
		return -ENOMEM;
	drm_gem_private_object_init(adev->ddev, &bo->gem_base, size);
	INIT_LIST_HEAD(&bo->shadow_list);
	INIT_LIST_HEAD(&bo->va);
	bo->preferred_domains = bp->preferred_domain ? bp->preferred_domain :
		bp->domain;
	bo->allowed_domains = bo->preferred_domains;
	if (bp->type != ttm_bo_type_kernel &&
	    bo->allowed_domains == AMDGPU_GEM_DOMAIN_VRAM)
		bo->allowed_domains |= AMDGPU_GEM_DOMAIN_GTT;

	bo->flags = bp->flags;

#ifdef CONFIG_X86_32
	/* XXX: Write-combined CPU mappings of GTT seem broken on 32-bit
	 * See https://bugs.freedesktop.org/show_bug.cgi?id=84627
	 */
	bo->flags &= ~AMDGPU_GEM_CREATE_CPU_GTT_USWC;
#elif defined(CONFIG_X86) && !defined(CONFIG_X86_PAT)
	/* Don't try to enable write-combining when it can't work, or things
	 * may be slow
	 * See https://bugs.freedesktop.org/show_bug.cgi?id=88758
	 */

#ifndef CONFIG_COMPILE_TEST
#warning Please enable CONFIG_MTRR and CONFIG_X86_PAT for better performance \
	 thanks to write-combining
#endif

	if (bo->flags & AMDGPU_GEM_CREATE_CPU_GTT_USWC)
		DRM_INFO_ONCE("Please enable CONFIG_MTRR and CONFIG_X86_PAT for "
			      "better performance thanks to write-combining\n");
	bo->flags &= ~AMDGPU_GEM_CREATE_CPU_GTT_USWC;
#else
	/* For architectures that don't support WC memory,
	 * mask out the WC flag from the BO
	 */
	if (!drm_arch_can_wc_memory())
		bo->flags &= ~AMDGPU_GEM_CREATE_CPU_GTT_USWC;
#endif

	bo->tbo.bdev = &adev->mman.bdev;
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

		r = amdgpu_fill_buffer(bo, 0, bo->tbo.resv, &fence);
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
		ww_mutex_unlock(&bo->tbo.resv->lock);
	amdgpu_bo_unref(&bo);
	return r;
}