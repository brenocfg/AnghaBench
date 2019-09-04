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
typedef  int u8 ;
struct perf_amd_iommu {int max_banks; int max_counters; unsigned long long cntr_assign_mask; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int clear_avail_iommu_bnk_cntr(struct perf_amd_iommu *perf_iommu,
					u8 bank, u8 cntr)
{
	unsigned long flags;
	int max_banks, max_cntrs;
	int shift = 0;

	max_banks = perf_iommu->max_banks;
	max_cntrs = perf_iommu->max_counters;

	if ((bank > max_banks) || (cntr > max_cntrs))
		return -EINVAL;

	shift = bank + cntr + (bank*3);

	raw_spin_lock_irqsave(&perf_iommu->lock, flags);
	perf_iommu->cntr_assign_mask &= ~(1ULL<<shift);
	raw_spin_unlock_irqrestore(&perf_iommu->lock, flags);

	return 0;
}