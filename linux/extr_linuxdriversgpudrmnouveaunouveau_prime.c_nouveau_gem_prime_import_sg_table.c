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
typedef  int /*<<< orphan*/  u32 ;
struct sg_table {int dummy; } ;
struct reservation_object {int /*<<< orphan*/  lock; } ;
struct nouveau_drm {int /*<<< orphan*/  client; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {TYPE_2__ mem; } ;
struct nouveau_bo {struct drm_gem_object gem; TYPE_3__ bo; int /*<<< orphan*/  valid_domains; } ;
struct drm_device {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; struct reservation_object* resv; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  NOUVEAU_GEM_DOMAIN_GART ; 
 int /*<<< orphan*/  TTM_PL_FLAG_TT ; 
 int drm_gem_object_init (struct drm_device*,struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int nouveau_bo_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sg_table*,struct reservation_object*,struct nouveau_bo**) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,struct nouveau_bo**) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  ww_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ww_mutex_unlock (int /*<<< orphan*/ *) ; 

struct drm_gem_object *nouveau_gem_prime_import_sg_table(struct drm_device *dev,
							 struct dma_buf_attachment *attach,
							 struct sg_table *sg)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_bo *nvbo;
	struct reservation_object *robj = attach->dmabuf->resv;
	u32 flags = 0;
	int ret;

	flags = TTM_PL_FLAG_TT;

	ww_mutex_lock(&robj->lock, NULL);
	ret = nouveau_bo_new(&drm->client, attach->dmabuf->size, 0, flags, 0, 0,
			     sg, robj, &nvbo);
	ww_mutex_unlock(&robj->lock);
	if (ret)
		return ERR_PTR(ret);

	nvbo->valid_domains = NOUVEAU_GEM_DOMAIN_GART;

	/* Initialize the embedded gem-object. We return a single gem-reference
	 * to the caller, instead of a normal nouveau_bo ttm reference. */
	ret = drm_gem_object_init(dev, &nvbo->gem, nvbo->bo.mem.size);
	if (ret) {
		nouveau_bo_ref(NULL, &nvbo);
		return ERR_PTR(-ENOMEM);
	}

	return &nvbo->gem;
}