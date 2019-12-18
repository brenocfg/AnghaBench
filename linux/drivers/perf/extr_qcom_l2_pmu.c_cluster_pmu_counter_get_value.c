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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IA_L2PMXEVCNTR ; 
 int /*<<< orphan*/  L2PMCCNTR ; 
 int /*<<< orphan*/  get_l2_indirect_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ l2_cycle_ctr_idx ; 
 int /*<<< orphan*/  reg_idx (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u64 cluster_pmu_counter_get_value(u32 idx)
{
	u64 value;

	if (idx == l2_cycle_ctr_idx)
		value = get_l2_indirect_reg(L2PMCCNTR);
	else
		value = get_l2_indirect_reg(reg_idx(IA_L2PMXEVCNTR, idx));

	return value;
}