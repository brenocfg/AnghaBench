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
struct xgene_pmu_dev {int max_counters; int /*<<< orphan*/  cntr_assign_mask; } ;

/* Variables and functions */
 int ENOSPC ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_next_avail_cntr(struct xgene_pmu_dev *pmu_dev)
{
	int cntr;

	cntr = find_first_zero_bit(pmu_dev->cntr_assign_mask,
				pmu_dev->max_counters);
	if (cntr == pmu_dev->max_counters)
		return -ENOSPC;
	set_bit(cntr, pmu_dev->cntr_assign_mask);

	return cntr;
}