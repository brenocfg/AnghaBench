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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int _KERNPG_TABLE ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pmd (int) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_pte_page(pmd_t *pmd)
{
	pte_t *pte = (pte_t *)get_zeroed_page(GFP_KERNEL);
	if (!pte)
		return -1;

	set_pmd(pmd, __pmd(__pa(pte) | _KERNPG_TABLE));
	return 0;
}