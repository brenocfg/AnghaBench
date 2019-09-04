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
struct rockchip_gem_object {int /*<<< orphan*/  kvaddr; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  VM_MAP ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int rockchip_gem_get_pages (struct rockchip_gem_object*) ; 
 int rockchip_gem_iommu_map (struct rockchip_gem_object*) ; 
 int /*<<< orphan*/  rockchip_gem_iommu_unmap (struct rockchip_gem_object*) ; 
 int /*<<< orphan*/  rockchip_gem_put_pages (struct rockchip_gem_object*) ; 
 int /*<<< orphan*/  vmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_gem_alloc_iommu(struct rockchip_gem_object *rk_obj,
				    bool alloc_kmap)
{
	int ret;

	ret = rockchip_gem_get_pages(rk_obj);
	if (ret < 0)
		return ret;

	ret = rockchip_gem_iommu_map(rk_obj);
	if (ret < 0)
		goto err_free;

	if (alloc_kmap) {
		rk_obj->kvaddr = vmap(rk_obj->pages, rk_obj->num_pages, VM_MAP,
				      pgprot_writecombine(PAGE_KERNEL));
		if (!rk_obj->kvaddr) {
			DRM_ERROR("failed to vmap() buffer\n");
			ret = -ENOMEM;
			goto err_unmap;
		}
	}

	return 0;

err_unmap:
	rockchip_gem_iommu_unmap(rk_obj);
err_free:
	rockchip_gem_put_pages(rk_obj);

	return ret;
}