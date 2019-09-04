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

/* Variables and functions */
 int PUD_TABLE_BIT ; 
 int pud_val (int /*<<< orphan*/ ) ; 

int pud_huge(pud_t pud)
{
#ifndef __PAGETABLE_PMD_FOLDED
	return pud_val(pud) && !(pud_val(pud) & PUD_TABLE_BIT);
#else
	return 0;
#endif
}