#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pte; } ;
typedef  TYPE_1__ pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  _PAGE_BIT_ACCESSED ; 
 scalar_t__ pte_young (TYPE_1__) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 

int ptep_test_and_clear_young(struct vm_area_struct *vma,
			      unsigned long addr, pte_t *ptep)
{
	int ret = 0;

	if (pte_young(*ptep))
		ret = test_and_clear_bit(_PAGE_BIT_ACCESSED,
					 (unsigned long *) &ptep->pte);

	return ret;
}