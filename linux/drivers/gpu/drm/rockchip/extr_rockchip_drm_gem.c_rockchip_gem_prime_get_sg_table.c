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
struct sg_table {int dummy; } ;
struct rockchip_gem_object {int /*<<< orphan*/  dma_attrs; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  kvaddr; int /*<<< orphan*/  num_pages; scalar_t__ pages; } ;
struct drm_gem_object {int /*<<< orphan*/  size; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOMEM ; 
 struct sg_table* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dma_get_sgtable_attrs (int /*<<< orphan*/ ,struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sg_table* drm_prime_pages_to_sg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct sg_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct rockchip_gem_object* to_rockchip_obj (struct drm_gem_object*) ; 

struct sg_table *rockchip_gem_prime_get_sg_table(struct drm_gem_object *obj)
{
	struct rockchip_gem_object *rk_obj = to_rockchip_obj(obj);
	struct drm_device *drm = obj->dev;
	struct sg_table *sgt;
	int ret;

	if (rk_obj->pages)
		return drm_prime_pages_to_sg(rk_obj->pages, rk_obj->num_pages);

	sgt = kzalloc(sizeof(*sgt), GFP_KERNEL);
	if (!sgt)
		return ERR_PTR(-ENOMEM);

	ret = dma_get_sgtable_attrs(drm->dev, sgt, rk_obj->kvaddr,
				    rk_obj->dma_addr, obj->size,
				    rk_obj->dma_attrs);
	if (ret) {
		DRM_ERROR("failed to allocate sgt, %d\n", ret);
		kfree(sgt);
		return ERR_PTR(ret);
	}

	return sgt;
}