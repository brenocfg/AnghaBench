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
typedef  int arm_v7s_iopte ;

/* Variables and functions */
 int ARM_V7S_CONT_SECTION ; 
 int /*<<< orphan*/  ARM_V7S_PTE_IS_TABLE (int,int) ; 
 int ARM_V7S_PTE_TYPE_PAGE ; 

__attribute__((used)) static bool arm_v7s_pte_is_cont(arm_v7s_iopte pte, int lvl)
{
	if (lvl == 1 && !ARM_V7S_PTE_IS_TABLE(pte, lvl))
		return pte & ARM_V7S_CONT_SECTION;
	else if (lvl == 2)
		return !(pte & ARM_V7S_PTE_TYPE_PAGE);
	return false;
}