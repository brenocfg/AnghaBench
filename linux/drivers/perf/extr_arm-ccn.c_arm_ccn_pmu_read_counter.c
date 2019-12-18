#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ base; } ;
struct arm_ccn {TYPE_1__ dt; } ;

/* Variables and functions */
 scalar_t__ CCN_DT_PMCCNTR ; 
 scalar_t__ CCN_DT_PMCCNTRSR ; 
 scalar_t__ CCN_DT_PMEVCNT (int) ; 
 scalar_t__ CCN_DT_PMSR ; 
 scalar_t__ CCN_DT_PMSR_CLR ; 
 scalar_t__ CCN_DT_PMSR_REQ ; 
 int CCN_IDX_PMU_CYCLE_COUNTER ; 
 int readl (scalar_t__) ; 
 int readq (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static u64 arm_ccn_pmu_read_counter(struct arm_ccn *ccn, int idx)
{
	u64 res;

	if (idx == CCN_IDX_PMU_CYCLE_COUNTER) {
#ifdef readq
		res = readq(ccn->dt.base + CCN_DT_PMCCNTR);
#else
		/* 40 bit counter, can do snapshot and read in two parts */
		writel(0x1, ccn->dt.base + CCN_DT_PMSR_REQ);
		while (!(readl(ccn->dt.base + CCN_DT_PMSR) & 0x1))
			;
		writel(0x1, ccn->dt.base + CCN_DT_PMSR_CLR);
		res = readl(ccn->dt.base + CCN_DT_PMCCNTRSR + 4) & 0xff;
		res <<= 32;
		res |= readl(ccn->dt.base + CCN_DT_PMCCNTRSR);
#endif
	} else {
		res = readl(ccn->dt.base + CCN_DT_PMEVCNT(idx));
	}

	return res;
}