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
struct mm_struct {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long DSISR_ISSTORE ; 
 unsigned long DSISR_NOHPTE ; 
 unsigned long HPTE_NOHPTE_UPDATE ; 
 unsigned long MSR_PR ; 
 scalar_t__ REGION_ID (unsigned long) ; 
 scalar_t__ USER_REGION_ID ; 
 scalar_t__ VMALLOC_REGION_ID ; 
 unsigned long _PAGE_EXEC ; 
 unsigned long _PAGE_PRESENT ; 
 unsigned long _PAGE_PRIVILEGED ; 
 unsigned long _PAGE_READ ; 
 unsigned long _PAGE_WRITE ; 
 TYPE_1__* current ; 
 int hash_page_mm (struct mm_struct*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 struct mm_struct init_mm ; 

int __hash_page(unsigned long ea, unsigned long msr, unsigned long trap,
		unsigned long dsisr)
{
	unsigned long access = _PAGE_PRESENT | _PAGE_READ;
	unsigned long flags = 0;
	struct mm_struct *mm = current->mm;

	if (REGION_ID(ea) == VMALLOC_REGION_ID)
		mm = &init_mm;

	if (dsisr & DSISR_NOHPTE)
		flags |= HPTE_NOHPTE_UPDATE;

	if (dsisr & DSISR_ISSTORE)
		access |= _PAGE_WRITE;
	/*
	 * We set _PAGE_PRIVILEGED only when
	 * kernel mode access kernel space.
	 *
	 * _PAGE_PRIVILEGED is NOT set
	 * 1) when kernel mode access user space
	 * 2) user space access kernel space.
	 */
	access |= _PAGE_PRIVILEGED;
	if ((msr & MSR_PR) || (REGION_ID(ea) == USER_REGION_ID))
		access &= ~_PAGE_PRIVILEGED;

	if (trap == 0x400)
		access |= _PAGE_EXEC;

	return hash_page_mm(mm, ea, access, trap, flags);
}