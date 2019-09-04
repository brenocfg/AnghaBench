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
struct vm_area_struct {int /*<<< orphan*/  vm_private_data; } ;
struct file {int dummy; } ;
struct etnaviv_gem_object {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* mmap ) (struct etnaviv_gem_object*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int drm_gem_mmap (struct file*,struct vm_area_struct*) ; 
 int stub1 (struct etnaviv_gem_object*,struct vm_area_struct*) ; 
 struct etnaviv_gem_object* to_etnaviv_bo (int /*<<< orphan*/ ) ; 

int etnaviv_gem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct etnaviv_gem_object *obj;
	int ret;

	ret = drm_gem_mmap(filp, vma);
	if (ret) {
		DBG("mmap failed: %d", ret);
		return ret;
	}

	obj = to_etnaviv_bo(vma->vm_private_data);
	return obj->ops->mmap(obj, vma);
}