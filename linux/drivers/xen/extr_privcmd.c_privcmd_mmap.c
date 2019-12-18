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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int VM_DONTCOPY ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int /*<<< orphan*/  privcmd_vm_ops ; 

__attribute__((used)) static int privcmd_mmap(struct file *file, struct vm_area_struct *vma)
{
	/* DONTCOPY is essential for Xen because copy_page_range doesn't know
	 * how to recreate these mappings */
	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTCOPY |
			 VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &privcmd_vm_ops;
	vma->vm_private_data = NULL;

	return 0;
}