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
struct xen_gem_object {int dummy; } ;
struct vm_area_struct {struct drm_gem_object* vm_private_data; } ;
struct file {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int drm_gem_mmap (struct file*,struct vm_area_struct*) ; 
 int gem_mmap_obj (struct xen_gem_object*,struct vm_area_struct*) ; 
 struct xen_gem_object* to_xen_gem_obj (struct drm_gem_object*) ; 

int xen_drm_front_gem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct xen_gem_object *xen_obj;
	struct drm_gem_object *gem_obj;
	int ret;

	ret = drm_gem_mmap(filp, vma);
	if (ret < 0)
		return ret;

	gem_obj = vma->vm_private_data;
	xen_obj = to_xen_gem_obj(gem_obj);
	return gem_mmap_obj(xen_obj, vma);
}