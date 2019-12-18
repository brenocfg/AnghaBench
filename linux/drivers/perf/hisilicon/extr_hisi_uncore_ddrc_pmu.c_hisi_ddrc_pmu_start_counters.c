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
struct hisi_pmu {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DDRC_PERF_CTRL ; 
 int /*<<< orphan*/  DDRC_PERF_CTRL_EN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hisi_ddrc_pmu_start_counters(struct hisi_pmu *ddrc_pmu)
{
	u32 val;

	/* Set perf_enable in DDRC_PERF_CTRL to start event counting */
	val = readl(ddrc_pmu->base + DDRC_PERF_CTRL);
	val |= DDRC_PERF_CTRL_EN;
	writel(val, ddrc_pmu->base + DDRC_PERF_CTRL);
}