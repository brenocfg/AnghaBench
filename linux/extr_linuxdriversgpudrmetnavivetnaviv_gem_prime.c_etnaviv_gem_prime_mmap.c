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
struct vm_area_struct {int dummy; } ;
struct etnaviv_gem_object {TYPE_1__* ops; } ;
struct drm_gem_object {int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int (* mmap ) (struct etnaviv_gem_object*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int drm_gem_mmap_obj (struct drm_gem_object*,int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int stub1 (struct etnaviv_gem_object*,struct vm_area_struct*) ; 
 struct etnaviv_gem_object* to_etnaviv_bo (struct drm_gem_object*) ; 

int etnaviv_gem_prime_mmap(struct drm_gem_object *obj,
			   struct vm_area_struct *vma)
{
	struct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	int ret;

	ret = drm_gem_mmap_obj(obj, obj->size, vma);
	if (ret < 0)
		return ret;

	return etnaviv_obj->ops->mmap(etnaviv_obj, vma);
}