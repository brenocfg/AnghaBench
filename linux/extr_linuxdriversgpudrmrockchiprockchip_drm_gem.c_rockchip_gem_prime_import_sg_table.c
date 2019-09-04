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
struct drm_gem_object {int dummy; } ;
struct rockchip_gem_object {struct drm_gem_object base; } ;
struct rockchip_drm_private {scalar_t__ domain; } ;
struct drm_device {struct rockchip_drm_private* dev_private; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 struct drm_gem_object* ERR_CAST (struct rockchip_gem_object*) ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct rockchip_gem_object*) ; 
 struct rockchip_gem_object* rockchip_gem_alloc_object (struct drm_device*,int /*<<< orphan*/ ) ; 
 int rockchip_gem_dma_map_sg (struct drm_device*,struct dma_buf_attachment*,struct sg_table*,struct rockchip_gem_object*) ; 
 int rockchip_gem_iommu_map_sg (struct drm_device*,struct dma_buf_attachment*,struct sg_table*,struct rockchip_gem_object*) ; 
 int /*<<< orphan*/  rockchip_gem_release_object (struct rockchip_gem_object*) ; 

struct drm_gem_object *
rockchip_gem_prime_import_sg_table(struct drm_device *drm,
				   struct dma_buf_attachment *attach,
				   struct sg_table *sg)
{
	struct rockchip_drm_private *private = drm->dev_private;
	struct rockchip_gem_object *rk_obj;
	int ret;

	rk_obj = rockchip_gem_alloc_object(drm, attach->dmabuf->size);
	if (IS_ERR(rk_obj))
		return ERR_CAST(rk_obj);

	if (private->domain)
		ret = rockchip_gem_iommu_map_sg(drm, attach, sg, rk_obj);
	else
		ret = rockchip_gem_dma_map_sg(drm, attach, sg, rk_obj);

	if (ret < 0) {
		DRM_ERROR("failed to import sg table: %d\n", ret);
		goto err_free_rk_obj;
	}

	return &rk_obj->base;

err_free_rk_obj:
	rockchip_gem_release_object(rk_obj);
	return ERR_PTR(ret);
}