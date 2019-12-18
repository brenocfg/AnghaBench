#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mtk_drm_private {int /*<<< orphan*/  dma_dev; } ;
struct drm_gem_object {int /*<<< orphan*/  size; } ;
struct mtk_drm_gem_obj {int /*<<< orphan*/  dma_addr; scalar_t__ cookie; scalar_t__ kvaddr; int /*<<< orphan*/  dma_attrs; struct drm_gem_object base; } ;
struct drm_device {struct mtk_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NO_KERNEL_MAPPING ; 
 int /*<<< orphan*/  DMA_ATTR_WRITE_COMBINE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct mtk_drm_gem_obj* ERR_CAST (struct mtk_drm_gem_obj*) ; 
 struct mtk_drm_gem_obj* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mtk_drm_gem_obj*) ; 
 scalar_t__ dma_alloc_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct mtk_drm_gem_obj*) ; 
 struct mtk_drm_gem_obj* mtk_drm_gem_init (struct drm_device*,size_t) ; 

struct mtk_drm_gem_obj *mtk_drm_gem_create(struct drm_device *dev,
					   size_t size, bool alloc_kmap)
{
	struct mtk_drm_private *priv = dev->dev_private;
	struct mtk_drm_gem_obj *mtk_gem;
	struct drm_gem_object *obj;
	int ret;

	mtk_gem = mtk_drm_gem_init(dev, size);
	if (IS_ERR(mtk_gem))
		return ERR_CAST(mtk_gem);

	obj = &mtk_gem->base;

	mtk_gem->dma_attrs = DMA_ATTR_WRITE_COMBINE;

	if (!alloc_kmap)
		mtk_gem->dma_attrs |= DMA_ATTR_NO_KERNEL_MAPPING;

	mtk_gem->cookie = dma_alloc_attrs(priv->dma_dev, obj->size,
					  &mtk_gem->dma_addr, GFP_KERNEL,
					  mtk_gem->dma_attrs);
	if (!mtk_gem->cookie) {
		DRM_ERROR("failed to allocate %zx byte dma buffer", obj->size);
		ret = -ENOMEM;
		goto err_gem_free;
	}

	if (alloc_kmap)
		mtk_gem->kvaddr = mtk_gem->cookie;

	DRM_DEBUG_DRIVER("cookie = %p dma_addr = %pad size = %zu\n",
			 mtk_gem->cookie, &mtk_gem->dma_addr,
			 size);

	return mtk_gem;

err_gem_free:
	drm_gem_object_release(obj);
	kfree(mtk_gem);
	return ERR_PTR(ret);
}