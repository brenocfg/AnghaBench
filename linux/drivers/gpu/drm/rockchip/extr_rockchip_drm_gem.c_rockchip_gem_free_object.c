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
struct rockchip_gem_object {TYPE_1__* sgt; } ;
struct rockchip_drm_private {scalar_t__ domain; } ;
struct drm_gem_object {scalar_t__ import_attach; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; struct rockchip_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,TYPE_1__*) ; 
 int /*<<< orphan*/  rockchip_gem_free_buf (struct rockchip_gem_object*) ; 
 int /*<<< orphan*/  rockchip_gem_iommu_unmap (struct rockchip_gem_object*) ; 
 int /*<<< orphan*/  rockchip_gem_release_object (struct rockchip_gem_object*) ; 
 struct rockchip_gem_object* to_rockchip_obj (struct drm_gem_object*) ; 

void rockchip_gem_free_object(struct drm_gem_object *obj)
{
	struct drm_device *drm = obj->dev;
	struct rockchip_drm_private *private = drm->dev_private;
	struct rockchip_gem_object *rk_obj = to_rockchip_obj(obj);

	if (obj->import_attach) {
		if (private->domain) {
			rockchip_gem_iommu_unmap(rk_obj);
		} else {
			dma_unmap_sg(drm->dev, rk_obj->sgt->sgl,
				     rk_obj->sgt->nents, DMA_BIDIRECTIONAL);
		}
		drm_prime_gem_destroy(obj, rk_obj->sgt);
	} else {
		rockchip_gem_free_buf(rk_obj);
	}

	rockchip_gem_release_object(rk_obj);
}