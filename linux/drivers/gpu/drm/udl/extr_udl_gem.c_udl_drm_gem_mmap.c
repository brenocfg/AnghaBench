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
struct vm_area_struct {int /*<<< orphan*/  vm_private_data; int /*<<< orphan*/  vm_flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MIXEDMAP ; 
 int /*<<< orphan*/  VM_PFNMAP ; 
 int drm_gem_mmap (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  to_udl_bo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_vm_cache_attr (int /*<<< orphan*/ ,struct vm_area_struct*) ; 

int udl_drm_gem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int ret;

	ret = drm_gem_mmap(filp, vma);
	if (ret)
		return ret;

	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_flags |= VM_MIXEDMAP;

	update_vm_cache_attr(to_udl_bo(vma->vm_private_data), vma);

	return ret;
}