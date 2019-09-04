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

/* Variables and functions */
 unsigned long _PAGE_INDEX ; 
 unsigned long _PAGE_SHIFT ; 
 unsigned long base_lra (unsigned long) ; 
 unsigned long base_page_addr_end (unsigned long,unsigned long) ; 

__attribute__((used)) static int base_page_walk(unsigned long origin, unsigned long addr,
			  unsigned long end, int alloc)
{
	unsigned long *pte, next;

	if (!alloc)
		return 0;
	pte = (unsigned long *) origin;
	pte += (addr & _PAGE_INDEX) >> _PAGE_SHIFT;
	do {
		next = base_page_addr_end(addr, end);
		*pte = base_lra(addr);
	} while (pte++, addr = next, addr < end);
	return 0;
}