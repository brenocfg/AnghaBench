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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  L2PMCNTENSET ; 
 int /*<<< orphan*/  idx_to_reg_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_l2_indirect_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cluster_pmu_counter_enable(u32 idx)
{
	set_l2_indirect_reg(L2PMCNTENSET, idx_to_reg_bit(idx));
}