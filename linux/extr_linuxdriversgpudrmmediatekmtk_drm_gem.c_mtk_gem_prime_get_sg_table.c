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
struct sg_table {int dummy; } ;
struct mtk_drm_private {int /*<<< orphan*/  dma_dev; } ;
struct mtk_drm_gem_obj {int /*<<< orphan*/  dma_attrs; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cookie; } ;
struct drm_gem_object {int /*<<< orphan*/  size; TYPE_1__* dev; } ;
struct TYPE_2__ {struct mtk_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOMEM ; 
 struct sg_table* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dma_get_sgtable_attrs (int /*<<< orphan*/ ,struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct sg_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mtk_drm_gem_obj* to_mtk_gem_obj (struct drm_gem_object*) ; 

struct sg_table *mtk_gem_prime_get_sg_table(struct drm_gem_object *obj)
{
	struct mtk_drm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	struct mtk_drm_private *priv = obj->dev->dev_private;
	struct sg_table *sgt;
	int ret;

	sgt = kzalloc(sizeof(*sgt), GFP_KERNEL);
	if (!sgt)
		return ERR_PTR(-ENOMEM);

	ret = dma_get_sgtable_attrs(priv->dma_dev, sgt, mtk_gem->cookie,
				    mtk_gem->dma_addr, obj->size,
				    mtk_gem->dma_attrs);
	if (ret) {
		DRM_ERROR("failed to allocate sgt, %d\n", ret);
		kfree(sgt);
		return ERR_PTR(ret);
	}

	return sgt;
}