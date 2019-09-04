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
struct vm_area_struct {unsigned long vm_flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned long VM_DONTDUMP ; 
 unsigned long VM_DONTEXPAND ; 
 int drm_gem_mmap (struct file*,struct vm_area_struct*) ; 

__attribute__((used)) static int vgem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long flags = vma->vm_flags;
	int ret;

	ret = drm_gem_mmap(filp, vma);
	if (ret)
		return ret;

	/* Keep the WC mmaping set by drm_gem_mmap() but our pages
	 * are ordinary and not special.
	 */
	vma->vm_flags = flags | VM_DONTEXPAND | VM_DONTDUMP;
	return 0;
}