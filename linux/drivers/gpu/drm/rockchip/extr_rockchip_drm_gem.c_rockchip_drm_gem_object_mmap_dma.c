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
struct vm_area_struct {int dummy; } ;
struct rockchip_gem_object {int /*<<< orphan*/  dma_attrs; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  kvaddr; } ;
struct drm_gem_object {int /*<<< orphan*/  size; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int dma_mmap_attrs (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rockchip_gem_object* to_rockchip_obj (struct drm_gem_object*) ; 

__attribute__((used)) static int rockchip_drm_gem_object_mmap_dma(struct drm_gem_object *obj,
					    struct vm_area_struct *vma)
{
	struct rockchip_gem_object *rk_obj = to_rockchip_obj(obj);
	struct drm_device *drm = obj->dev;

	return dma_mmap_attrs(drm->dev, vma, rk_obj->kvaddr, rk_obj->dma_addr,
			      obj->size, rk_obj->dma_attrs);
}