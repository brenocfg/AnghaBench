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
struct drm_gem_object {struct drm_device* dev; } ;
struct rockchip_gem_object {struct drm_gem_object base; } ;
struct rockchip_drm_private {scalar_t__ domain; } ;
struct drm_device {struct rockchip_drm_private* dev_private; } ;

/* Variables and functions */
 int rockchip_gem_alloc_dma (struct rockchip_gem_object*,int) ; 
 int rockchip_gem_alloc_iommu (struct rockchip_gem_object*,int) ; 

__attribute__((used)) static int rockchip_gem_alloc_buf(struct rockchip_gem_object *rk_obj,
				  bool alloc_kmap)
{
	struct drm_gem_object *obj = &rk_obj->base;
	struct drm_device *drm = obj->dev;
	struct rockchip_drm_private *private = drm->dev_private;

	if (private->domain)
		return rockchip_gem_alloc_iommu(rk_obj, alloc_kmap);
	else
		return rockchip_gem_alloc_dma(rk_obj, alloc_kmap);
}