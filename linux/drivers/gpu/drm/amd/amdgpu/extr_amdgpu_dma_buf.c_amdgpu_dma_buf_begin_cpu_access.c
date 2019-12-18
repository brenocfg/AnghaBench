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
typedef  int u32 ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct dma_buf {int /*<<< orphan*/  priv; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {int allowed_domains; int /*<<< orphan*/  placement; TYPE_1__ tbo; int /*<<< orphan*/  pin_count; int /*<<< orphan*/  flags; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int AMDGPU_GEM_DOMAIN_GTT ; 
 int DMA_BIDIRECTIONAL ; 
 int DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,int) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int amdgpu_display_supported_domains (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (TYPE_1__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int amdgpu_dma_buf_begin_cpu_access(struct dma_buf *dma_buf,
					   enum dma_data_direction direction)
{
	struct amdgpu_bo *bo = gem_to_amdgpu_bo(dma_buf->priv);
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	struct ttm_operation_ctx ctx = { true, false };
	u32 domain = amdgpu_display_supported_domains(adev, bo->flags);
	int ret;
	bool reads = (direction == DMA_BIDIRECTIONAL ||
		      direction == DMA_FROM_DEVICE);

	if (!reads || !(domain & AMDGPU_GEM_DOMAIN_GTT))
		return 0;

	/* move to gtt */
	ret = amdgpu_bo_reserve(bo, false);
	if (unlikely(ret != 0))
		return ret;

	if (!bo->pin_count && (bo->allowed_domains & AMDGPU_GEM_DOMAIN_GTT)) {
		amdgpu_bo_placement_from_domain(bo, AMDGPU_GEM_DOMAIN_GTT);
		ret = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
	}

	amdgpu_bo_unreserve(bo);
	return ret;
}