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
struct drm_gem_object {int /*<<< orphan*/  size; struct drm_device* dev; } ;
struct rockchip_gem_object {int /*<<< orphan*/  kvaddr; int /*<<< orphan*/  dma_attrs; int /*<<< orphan*/  dma_addr; struct drm_gem_object base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NO_KERNEL_MAPPING ; 
 int /*<<< orphan*/  DMA_ATTR_WRITE_COMBINE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_gem_alloc_dma(struct rockchip_gem_object *rk_obj,
				  bool alloc_kmap)
{
	struct drm_gem_object *obj = &rk_obj->base;
	struct drm_device *drm = obj->dev;

	rk_obj->dma_attrs = DMA_ATTR_WRITE_COMBINE;

	if (!alloc_kmap)
		rk_obj->dma_attrs |= DMA_ATTR_NO_KERNEL_MAPPING;

	rk_obj->kvaddr = dma_alloc_attrs(drm->dev, obj->size,
					 &rk_obj->dma_addr, GFP_KERNEL,
					 rk_obj->dma_attrs);
	if (!rk_obj->kvaddr) {
		DRM_ERROR("failed to allocate %zu byte dma buffer", obj->size);
		return -ENOMEM;
	}

	return 0;
}