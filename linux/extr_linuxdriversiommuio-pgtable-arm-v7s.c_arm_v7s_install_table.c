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
struct io_pgtable_cfg {int quirks; } ;
typedef  int arm_v7s_iopte ;

/* Variables and functions */
 int ARM_V7S_ATTR_NS_TABLE ; 
 int ARM_V7S_PTE_TYPE_TABLE ; 
 int IO_PGTABLE_QUIRK_ARM_NS ; 
 int /*<<< orphan*/  __arm_v7s_pte_sync (int*,int,struct io_pgtable_cfg*) ; 
 int cmpxchg_relaxed (int*,int,int) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int virt_to_phys (int*) ; 

__attribute__((used)) static arm_v7s_iopte arm_v7s_install_table(arm_v7s_iopte *table,
					   arm_v7s_iopte *ptep,
					   arm_v7s_iopte curr,
					   struct io_pgtable_cfg *cfg)
{
	arm_v7s_iopte old, new;

	new = virt_to_phys(table) | ARM_V7S_PTE_TYPE_TABLE;
	if (cfg->quirks & IO_PGTABLE_QUIRK_ARM_NS)
		new |= ARM_V7S_ATTR_NS_TABLE;

	/*
	 * Ensure the table itself is visible before its PTE can be.
	 * Whilst we could get away with cmpxchg64_release below, this
	 * doesn't have any ordering semantics when !CONFIG_SMP.
	 */
	dma_wmb();

	old = cmpxchg_relaxed(ptep, curr, new);
	__arm_v7s_pte_sync(ptep, 1, cfg);

	return old;
}