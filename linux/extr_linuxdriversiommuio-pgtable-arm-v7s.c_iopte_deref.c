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
typedef  int /*<<< orphan*/  arm_v7s_iopte ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_V7S_LVL_MASK (int) ; 
 scalar_t__ ARM_V7S_PTE_IS_TABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ARM_V7S_TABLE_MASK ; 
 int /*<<< orphan*/ * phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static arm_v7s_iopte *iopte_deref(arm_v7s_iopte pte, int lvl)
{
	if (ARM_V7S_PTE_IS_TABLE(pte, lvl))
		pte &= ARM_V7S_TABLE_MASK;
	else
		pte &= ARM_V7S_LVL_MASK(lvl);
	return phys_to_virt(pte);
}