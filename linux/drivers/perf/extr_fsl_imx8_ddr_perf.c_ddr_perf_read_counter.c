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
struct ddr_pmu {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ COUNTER_READ ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 ddr_perf_read_counter(struct ddr_pmu *pmu, int counter)
{
	return readl_relaxed(pmu->base + COUNTER_READ + counter * 4);
}