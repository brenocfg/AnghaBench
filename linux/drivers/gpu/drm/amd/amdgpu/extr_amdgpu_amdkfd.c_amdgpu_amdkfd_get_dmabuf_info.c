#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kgd_dev {int dummy; } ;
struct drm_gem_object {TYPE_2__* dev; } ;
struct dma_buf {struct drm_gem_object* priv; int /*<<< orphan*/ * ops; } ;
struct amdgpu_device {TYPE_1__* ddev; } ;
struct amdgpu_bo {int preferred_domains; int flags; int /*<<< orphan*/  metadata_size; } ;
struct TYPE_4__ {scalar_t__ driver; struct amdgpu_device* dev_private; } ;
struct TYPE_3__ {scalar_t__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_MEM_FLAGS_GTT ; 
 int /*<<< orphan*/  ALLOC_MEM_FLAGS_PUBLIC ; 
 int /*<<< orphan*/  ALLOC_MEM_FLAGS_VRAM ; 
 int AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int AMDGPU_GEM_DOMAIN_GTT ; 
 int AMDGPU_GEM_DOMAIN_VRAM ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 int PTR_ERR (struct dma_buf*) ; 
 int amdgpu_bo_get_metadata (struct amdgpu_bo*,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_size (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_dmabuf_ops ; 
 struct dma_buf* dma_buf_get (int) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 

int amdgpu_amdkfd_get_dmabuf_info(struct kgd_dev *kgd, int dma_buf_fd,
				  struct kgd_dev **dma_buf_kgd,
				  uint64_t *bo_size, void *metadata_buffer,
				  size_t buffer_size, uint32_t *metadata_size,
				  uint32_t *flags)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;
	struct dma_buf *dma_buf;
	struct drm_gem_object *obj;
	struct amdgpu_bo *bo;
	uint64_t metadata_flags;
	int r = -EINVAL;

	dma_buf = dma_buf_get(dma_buf_fd);
	if (IS_ERR(dma_buf))
		return PTR_ERR(dma_buf);

	if (dma_buf->ops != &amdgpu_dmabuf_ops)
		/* Can't handle non-graphics buffers */
		goto out_put;

	obj = dma_buf->priv;
	if (obj->dev->driver != adev->ddev->driver)
		/* Can't handle buffers from different drivers */
		goto out_put;

	adev = obj->dev->dev_private;
	bo = gem_to_amdgpu_bo(obj);
	if (!(bo->preferred_domains & (AMDGPU_GEM_DOMAIN_VRAM |
				    AMDGPU_GEM_DOMAIN_GTT)))
		/* Only VRAM and GTT BOs are supported */
		goto out_put;

	r = 0;
	if (dma_buf_kgd)
		*dma_buf_kgd = (struct kgd_dev *)adev;
	if (bo_size)
		*bo_size = amdgpu_bo_size(bo);
	if (metadata_size)
		*metadata_size = bo->metadata_size;
	if (metadata_buffer)
		r = amdgpu_bo_get_metadata(bo, metadata_buffer, buffer_size,
					   metadata_size, &metadata_flags);
	if (flags) {
		*flags = (bo->preferred_domains & AMDGPU_GEM_DOMAIN_VRAM) ?
			ALLOC_MEM_FLAGS_VRAM : ALLOC_MEM_FLAGS_GTT;

		if (bo->flags & AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED)
			*flags |= ALLOC_MEM_FLAGS_PUBLIC;
	}

out_put:
	dma_buf_put(dma_buf);
	return r;
}