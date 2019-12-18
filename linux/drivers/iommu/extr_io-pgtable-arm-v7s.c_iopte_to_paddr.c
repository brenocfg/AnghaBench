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
struct io_pgtable_cfg {int dummy; } ;
typedef  int phys_addr_t ;
typedef  int arm_v7s_iopte ;

/* Variables and functions */
 int ARM_V7S_ATTR_MTK_PA_BIT32 ; 
 int ARM_V7S_ATTR_MTK_PA_BIT33 ; 
 int ARM_V7S_CONT_PAGES ; 
 int ARM_V7S_LVL_MASK (int) ; 
 scalar_t__ ARM_V7S_PTE_IS_TABLE (int,int) ; 
 int ARM_V7S_TABLE_MASK ; 
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  arm_v7s_is_mtk_enabled (struct io_pgtable_cfg*) ; 
 scalar_t__ arm_v7s_pte_is_cont (int,int) ; 

__attribute__((used)) static phys_addr_t iopte_to_paddr(arm_v7s_iopte pte, int lvl,
				  struct io_pgtable_cfg *cfg)
{
	arm_v7s_iopte mask;
	phys_addr_t paddr;

	if (ARM_V7S_PTE_IS_TABLE(pte, lvl))
		mask = ARM_V7S_TABLE_MASK;
	else if (arm_v7s_pte_is_cont(pte, lvl))
		mask = ARM_V7S_LVL_MASK(lvl) * ARM_V7S_CONT_PAGES;
	else
		mask = ARM_V7S_LVL_MASK(lvl);

	paddr = pte & mask;
	if (!arm_v7s_is_mtk_enabled(cfg))
		return paddr;

	if (pte & ARM_V7S_ATTR_MTK_PA_BIT32)
		paddr |= BIT_ULL(32);
	if (pte & ARM_V7S_ATTR_MTK_PA_BIT33)
		paddr |= BIT_ULL(33);
	return paddr;
}