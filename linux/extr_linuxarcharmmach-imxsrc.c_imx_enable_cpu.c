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

/* Variables and functions */
 int BP_SRC_SCR_CORE1_ENABLE ; 
 int BP_SRC_SCR_CORE1_RST ; 
 scalar_t__ SRC_SCR ; 
 int cpu_logical_map (int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  scr_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ src_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void imx_enable_cpu(int cpu, bool enable)
{
	u32 mask, val;

	cpu = cpu_logical_map(cpu);
	mask = 1 << (BP_SRC_SCR_CORE1_ENABLE + cpu - 1);
	spin_lock(&scr_lock);
	val = readl_relaxed(src_base + SRC_SCR);
	val = enable ? val | mask : val & ~mask;
	val |= 1 << (BP_SRC_SCR_CORE1_RST + cpu - 1);
	writel_relaxed(val, src_base + SRC_SCR);
	spin_unlock(&scr_lock);
}