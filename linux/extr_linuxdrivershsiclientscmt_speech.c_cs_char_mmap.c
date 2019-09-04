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
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int vm_flags; int /*<<< orphan*/  vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int /*<<< orphan*/  cs_char_vm_ops ; 
 int vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static int cs_char_mmap(struct file *file, struct vm_area_struct *vma)
{
	if (vma->vm_end < vma->vm_start)
		return -EINVAL;

	if (vma_pages(vma) != 1)
		return -EINVAL;

	vma->vm_flags |= VM_IO | VM_DONTDUMP | VM_DONTEXPAND;
	vma->vm_ops = &cs_char_vm_ops;
	vma->vm_private_data = file->private_data;

	return 0;
}