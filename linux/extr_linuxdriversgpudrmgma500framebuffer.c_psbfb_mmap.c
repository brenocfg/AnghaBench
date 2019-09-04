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
struct vm_area_struct {unsigned long vm_pgoff; int vm_flags; void* vm_private_data; int /*<<< orphan*/ * vm_ops; TYPE_1__* vm_file; } ;
struct psb_framebuffer {scalar_t__ addr_space; } ;
struct psb_fbdev {struct psb_framebuffer pfb; } ;
struct fb_info {struct psb_fbdev* par; } ;
struct TYPE_2__ {scalar_t__ f_mapping; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_MIXEDMAP ; 
 int /*<<< orphan*/  psbfb_vm_ops ; 

__attribute__((used)) static int psbfb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct psb_fbdev *fbdev = info->par;
	struct psb_framebuffer *psbfb = &fbdev->pfb;

	if (vma->vm_pgoff != 0)
		return -EINVAL;
	if (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		return -EINVAL;

	if (!psbfb->addr_space)
		psbfb->addr_space = vma->vm_file->f_mapping;
	/*
	 * If this is a GEM object then info->screen_base is the virtual
	 * kernel remapping of the object. FIXME: Review if this is
	 * suitable for our mmap work
	 */
	vma->vm_ops = &psbfb_vm_ops;
	vma->vm_private_data = (void *)psbfb;
	vma->vm_flags |= VM_IO | VM_MIXEDMAP | VM_DONTEXPAND | VM_DONTDUMP;
	return 0;
}