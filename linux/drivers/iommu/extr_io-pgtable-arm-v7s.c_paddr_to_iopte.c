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
 int ARM_V7S_LVL_MASK (int) ; 
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  arm_v7s_is_mtk_enabled (struct io_pgtable_cfg*) ; 

__attribute__((used)) static arm_v7s_iopte paddr_to_iopte(phys_addr_t paddr, int lvl,
				    struct io_pgtable_cfg *cfg)
{
	arm_v7s_iopte pte = paddr & ARM_V7S_LVL_MASK(lvl);

	if (!arm_v7s_is_mtk_enabled(cfg))
		return pte;

	if (paddr & BIT_ULL(32))
		pte |= ARM_V7S_ATTR_MTK_PA_BIT32;
	if (paddr & BIT_ULL(33))
		pte |= ARM_V7S_ATTR_MTK_PA_BIT33;
	return pte;
}