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
struct rockchip_gem_object {int /*<<< orphan*/  pages; } ;
struct drm_gem_object {unsigned int size; } ;

/* Variables and functions */
 int ENXIO ; 
 unsigned int PAGE_SHIFT ; 
 struct rockchip_gem_object* to_rockchip_obj (struct drm_gem_object*) ; 
 int vm_map_pages (struct vm_area_struct*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static int rockchip_drm_gem_object_mmap_iommu(struct drm_gem_object *obj,
					      struct vm_area_struct *vma)
{
	struct rockchip_gem_object *rk_obj = to_rockchip_obj(obj);
	unsigned int count = obj->size >> PAGE_SHIFT;
	unsigned long user_count = vma_pages(vma);

	if (user_count == 0)
		return -ENXIO;

	return vm_map_pages(vma, rk_obj->pages, count);
}