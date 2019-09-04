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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int _PAGE_PMD_HUGE ; 
 int _PAGE_VALID ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 

int pmd_huge(pmd_t pmd)
{
	return !pmd_none(pmd) &&
		(pmd_val(pmd) & (_PAGE_VALID|_PAGE_PMD_HUGE)) != _PAGE_VALID;
}