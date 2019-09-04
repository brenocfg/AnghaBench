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
struct TYPE_2__ {unsigned long x86_virt_bits; } ;

/* Variables and functions */
 unsigned long bd_entry_virt_space (struct mm_struct*) ; 
 TYPE_1__ boot_cpu_data ; 
 scalar_t__ is_64bit_mm (struct mm_struct*) ; 

__attribute__((used)) static unsigned long mpx_get_bd_entry_offset(struct mm_struct *mm,
		unsigned long addr)
{
	/*
	 * There are several ways to derive the bd offsets.  We
	 * use the following approach here:
	 * 1. We know the size of the virtual address space
	 * 2. We know the number of entries in a bounds table
	 * 3. We know that each entry covers a fixed amount of
	 *    virtual address space.
	 * So, we can just divide the virtual address by the
	 * virtual space used by one entry to determine which
	 * entry "controls" the given virtual address.
	 */
	if (is_64bit_mm(mm)) {
		int bd_entry_size = 8; /* 64-bit pointer */
		/*
		 * Take the 64-bit addressing hole in to account.
		 */
		addr &= ((1UL << boot_cpu_data.x86_virt_bits) - 1);
		return (addr / bd_entry_virt_space(mm)) * bd_entry_size;
	} else {
		int bd_entry_size = 4; /* 32-bit pointer */
		/*
		 * 32-bit has no hole so this case needs no mask
		 */
		return (addr / bd_entry_virt_space(mm)) * bd_entry_size;
	}
	/*
	 * The two return calls above are exact copies.  If we
	 * pull out a single copy and put it in here, gcc won't
	 * realize that we're doing a power-of-2 divide and use
	 * shifts.  It uses a real divide.  If we put them up
	 * there, it manages to figure it out (gcc 4.8.3).
	 */
}