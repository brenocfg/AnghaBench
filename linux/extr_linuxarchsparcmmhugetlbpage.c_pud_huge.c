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
 int _PAGE_PUD_HUGE ; 
 int _PAGE_VALID ; 
 int /*<<< orphan*/  pud_none (int /*<<< orphan*/ ) ; 
 int pud_val (int /*<<< orphan*/ ) ; 

int pud_huge(pud_t pud)
{
	return !pud_none(pud) &&
		(pud_val(pud) & (_PAGE_VALID|_PAGE_PUD_HUGE)) != _PAGE_VALID;
}