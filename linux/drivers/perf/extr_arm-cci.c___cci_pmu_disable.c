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
struct cci_pmu {scalar_t__ ctrl_base; } ;

/* Variables and functions */
 scalar_t__ CCI_PMCR ; 
 int CCI_PMCR_CEN ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void __cci_pmu_disable(struct cci_pmu *cci_pmu)
{
	u32 val;

	/* Disable all the PMU counters. */
	val = readl_relaxed(cci_pmu->ctrl_base + CCI_PMCR) & ~CCI_PMCR_CEN;
	writel(val, cci_pmu->ctrl_base + CCI_PMCR);
}