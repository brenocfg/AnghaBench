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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int /*<<< orphan*/  mon_bin_vm_ops ; 
 int /*<<< orphan*/  mon_bin_vma_open (struct vm_area_struct*) ; 

__attribute__((used)) static int mon_bin_mmap(struct file *filp, struct vm_area_struct *vma)
{
	/* don't do anything here: "fault" will set up page table entries */
	vma->vm_ops = &mon_bin_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_private_data = filp->private_data;
	mon_bin_vma_open(vma);
	return 0;
}