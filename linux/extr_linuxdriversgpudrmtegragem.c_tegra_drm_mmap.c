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
struct vm_area_struct {struct drm_gem_object* vm_private_data; } ;
struct file {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int __tegra_gem_mmap (struct drm_gem_object*,struct vm_area_struct*) ; 
 int drm_gem_mmap (struct file*,struct vm_area_struct*) ; 

int tegra_drm_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct drm_gem_object *gem;
	int err;

	err = drm_gem_mmap(file, vma);
	if (err < 0)
		return err;

	gem = vma->vm_private_data;

	return __tegra_gem_mmap(gem, vma);
}