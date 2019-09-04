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
struct vm_area_struct {int vm_flags; } ;

/* Variables and functions */
 int FAULT_CODE_ITLB ; 
 int FAULT_CODE_WRITE ; 
 int VM_EXEC ; 
 int VM_READ ; 
 int VM_WRITE ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int access_error(int error_code, struct vm_area_struct *vma)
{
	if (error_code & FAULT_CODE_WRITE) {
		/* write, present and write, not present: */
		if (unlikely(!(vma->vm_flags & VM_WRITE)))
			return 1;
		return 0;
	}

	/* ITLB miss on NX page */
	if (unlikely((error_code & FAULT_CODE_ITLB) &&
		     !(vma->vm_flags & VM_EXEC)))
		return 1;

	/* read, not present: */
	if (unlikely(!(vma->vm_flags & (VM_READ | VM_EXEC | VM_WRITE))))
		return 1;

	return 0;
}