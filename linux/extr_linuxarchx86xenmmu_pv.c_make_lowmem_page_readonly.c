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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ HYPERVISOR_update_va_mapping (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookup_address (unsigned long,unsigned int*) ; 
 int /*<<< orphan*/  pte_wrprotect (int /*<<< orphan*/ ) ; 

void make_lowmem_page_readonly(void *vaddr)
{
	pte_t *pte, ptev;
	unsigned long address = (unsigned long)vaddr;
	unsigned int level;

	pte = lookup_address(address, &level);
	if (pte == NULL)
		return;		/* vaddr missing */

	ptev = pte_wrprotect(*pte);

	if (HYPERVISOR_update_va_mapping(address, ptev, 0))
		BUG();
}