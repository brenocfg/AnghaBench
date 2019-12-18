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
struct drm_gem_object {int /*<<< orphan*/  size; } ;
struct drm_gem_cma_object {int dummy; } ;

/* Variables and functions */
 int drm_gem_cma_mmap_obj (struct drm_gem_cma_object*,struct vm_area_struct*) ; 
 int drm_gem_mmap_obj (struct drm_gem_object*,int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 struct drm_gem_cma_object* to_drm_gem_cma_obj (struct drm_gem_object*) ; 

int drm_gem_cma_prime_mmap(struct drm_gem_object *obj,
			   struct vm_area_struct *vma)
{
	struct drm_gem_cma_object *cma_obj;
	int ret;

	ret = drm_gem_mmap_obj(obj, obj->size, vma);
	if (ret < 0)
		return ret;

	cma_obj = to_drm_gem_cma_obj(obj);
	return drm_gem_cma_mmap_obj(cma_obj, vma);
}