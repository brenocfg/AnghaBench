#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_object {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dev; } ;
struct dma_buf {struct drm_gem_object* priv; } ;
struct amdgpu_device {TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {scalar_t__ prime_shared_count; TYPE_3__ tbo; } ;
struct TYPE_5__ {scalar_t__ driver; } ;
struct TYPE_4__ {scalar_t__ driver; } ;

/* Variables and functions */
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_map_detach (struct dma_buf*,struct dma_buf_attachment*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void amdgpu_dma_buf_map_detach(struct dma_buf *dma_buf,
				      struct dma_buf_attachment *attach)
{
	struct drm_gem_object *obj = dma_buf->priv;
	struct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	int ret = 0;

	ret = amdgpu_bo_reserve(bo, true);
	if (unlikely(ret != 0))
		goto error;

	amdgpu_bo_unpin(bo);
	if (attach->dev->driver != adev->dev->driver && bo->prime_shared_count)
		bo->prime_shared_count--;
	amdgpu_bo_unreserve(bo);

error:
	drm_gem_map_detach(dma_buf, attach);
}