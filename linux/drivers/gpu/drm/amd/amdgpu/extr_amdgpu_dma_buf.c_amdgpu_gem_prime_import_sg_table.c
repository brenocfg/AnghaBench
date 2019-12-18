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
struct sg_table {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct dma_resv {int dummy; } ;
struct dma_buf_attachment {TYPE_2__* dmabuf; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo_param {struct dma_resv* resv; int /*<<< orphan*/  type; scalar_t__ flags; int /*<<< orphan*/  domain; int /*<<< orphan*/  byte_align; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {struct drm_gem_object base; TYPE_1__* ttm; struct sg_table* sg; } ;
struct amdgpu_bo {int prime_shared_count; TYPE_3__ tbo; void* preferred_domains; void* allowed_domains; } ;
typedef  int /*<<< orphan*/  bp ;
struct TYPE_5__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  size; struct dma_resv* resv; } ;
struct TYPE_4__ {struct sg_table* sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_CPU ; 
 void* AMDGPU_GEM_DOMAIN_GTT ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create (struct amdgpu_device*,struct amdgpu_bo_param*,struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_dmabuf_ops ; 
 int /*<<< orphan*/  dma_resv_lock (struct dma_resv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_resv_unlock (struct dma_resv*) ; 
 int /*<<< orphan*/  memset (struct amdgpu_bo_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_type_sg ; 

struct drm_gem_object *
amdgpu_gem_prime_import_sg_table(struct drm_device *dev,
				 struct dma_buf_attachment *attach,
				 struct sg_table *sg)
{
	struct dma_resv *resv = attach->dmabuf->resv;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_bo *bo;
	struct amdgpu_bo_param bp;
	int ret;

	memset(&bp, 0, sizeof(bp));
	bp.size = attach->dmabuf->size;
	bp.byte_align = PAGE_SIZE;
	bp.domain = AMDGPU_GEM_DOMAIN_CPU;
	bp.flags = 0;
	bp.type = ttm_bo_type_sg;
	bp.resv = resv;
	dma_resv_lock(resv, NULL);
	ret = amdgpu_bo_create(adev, &bp, &bo);
	if (ret)
		goto error;

	bo->tbo.sg = sg;
	bo->tbo.ttm->sg = sg;
	bo->allowed_domains = AMDGPU_GEM_DOMAIN_GTT;
	bo->preferred_domains = AMDGPU_GEM_DOMAIN_GTT;
	if (attach->dmabuf->ops != &amdgpu_dmabuf_ops)
		bo->prime_shared_count = 1;

	dma_resv_unlock(resv);
	return &bo->tbo.base;

error:
	dma_resv_unlock(resv);
	return ERR_PTR(ret);
}