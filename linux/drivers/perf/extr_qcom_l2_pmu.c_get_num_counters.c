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

/* Variables and functions */
 int /*<<< orphan*/  L2PMCR ; 
 int L2PMCR_NUM_EV_MASK ; 
 int L2PMCR_NUM_EV_SHIFT ; 
 int get_l2_indirect_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_num_counters(void)
{
	int val;

	val = get_l2_indirect_reg(L2PMCR);

	/*
	 * Read number of counters from L2PMCR and add 1
	 * for the cycle counter.
	 */
	return ((val >> L2PMCR_NUM_EV_SHIFT) & L2PMCR_NUM_EV_MASK) + 1;
}