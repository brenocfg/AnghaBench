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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  __set_pte_vaddr (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int pud_index (unsigned long) ; 

void set_pte_vaddr_pud(pud_t *pud_page, unsigned long vaddr, pte_t new_pte)
{
	pud_t *pud = pud_page + pud_index(vaddr);

	__set_pte_vaddr(pud, vaddr, new_pte);
}