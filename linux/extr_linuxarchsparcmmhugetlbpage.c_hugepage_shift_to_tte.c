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
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  sun4u_hugepage_shift_to_tte (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sun4v_hugepage_shift_to_tte (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ tlb_type ; 

__attribute__((used)) static pte_t hugepage_shift_to_tte(pte_t entry, unsigned int shift)
{
	if (tlb_type == hypervisor)
		return sun4v_hugepage_shift_to_tte(entry, shift);
	else
		return sun4u_hugepage_shift_to_tte(entry, shift);
}