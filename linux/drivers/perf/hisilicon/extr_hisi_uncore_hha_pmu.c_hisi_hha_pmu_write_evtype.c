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
typedef  int u32 ;
struct hisi_pmu {int base; } ;

/* Variables and functions */
 int HHA_EVENT_TYPE0 ; 
 int HHA_EVTYPE_NONE ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void hisi_hha_pmu_write_evtype(struct hisi_pmu *hha_pmu, int idx,
				      u32 type)
{
	u32 reg, reg_idx, shift, val;

	/*
	 * Select the appropriate event select register(HHA_EVENT_TYPEx).
	 * There are 4 event select registers for the 16 hardware counters.
	 * Event code is 8-bits and for the first 4 hardware counters,
	 * HHA_EVENT_TYPE0 is chosen. For the next 4 hardware counters,
	 * HHA_EVENT_TYPE1 is chosen and so on.
	 */
	reg = HHA_EVENT_TYPE0 + 4 * (idx / 4);
	reg_idx = idx % 4;
	shift = 8 * reg_idx;

	/* Write event code to HHA_EVENT_TYPEx register */
	val = readl(hha_pmu->base + reg);
	val &= ~(HHA_EVTYPE_NONE << shift);
	val |= (type << shift);
	writel(val, hha_pmu->base + reg);
}