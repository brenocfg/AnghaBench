#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_object {int dummy; } ;
struct dma_buf_attachment {TYPE_3__* dev; } ;
struct dma_buf {struct drm_gem_object* priv; } ;
struct amdgpu_device {TYPE_4__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  resv; } ;
struct TYPE_6__ {TYPE_1__ base; int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {int /*<<< orphan*/  prime_shared_count; TYPE_2__ tbo; } ;
struct TYPE_8__ {scalar_t__ driver; } ;
struct TYPE_7__ {scalar_t__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 long __dma_resv_make_exclusive (int /*<<< orphan*/ ) ; 
 long amdgpu_bo_pin (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 long amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 long drm_gem_map_attach (struct dma_buf*,struct dma_buf_attachment*) ; 
 int /*<<< orphan*/  drm_gem_map_detach (struct dma_buf*,struct dma_buf_attachment*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int amdgpu_dma_buf_map_attach(struct dma_buf *dma_buf,
				     struct dma_buf_attachment *attach)
{
	struct drm_gem_object *obj = dma_buf->priv;
	struct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	long r;

	r = drm_gem_map_attach(dma_buf, attach);
	if (r)
		return r;

	r = amdgpu_bo_reserve(bo, false);
	if (unlikely(r != 0))
		goto error_detach;


	if (attach->dev->driver != adev->dev->driver) {
		/*
		 * We only create shared fences for internal use, but importers
		 * of the dmabuf rely on exclusive fences for implicitly
		 * tracking write hazards. As any of the current fences may
		 * correspond to a write, we need to convert all existing
		 * fences on the reservation object into a single exclusive
		 * fence.
		 */
		r = __dma_resv_make_exclusive(bo->tbo.base.resv);
		if (r)
			goto error_unreserve;
	}

	/* pin buffer into GTT */
	r = amdgpu_bo_pin(bo, AMDGPU_GEM_DOMAIN_GTT);
	if (r)
		goto error_unreserve;

	if (attach->dev->driver != adev->dev->driver)
		bo->prime_shared_count++;

error_unreserve:
	amdgpu_bo_unreserve(bo);

error_detach:
	if (r)
		drm_gem_map_detach(dma_buf, attach);
	return r;
}