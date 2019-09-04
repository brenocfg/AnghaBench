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
 scalar_t__ SLCR_REBOOT_STATUS_OFFSET ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 scalar_t__ zynq_slcr_base ; 

void zynq_slcr_cpu_state_write(int cpu, bool die)
{
	u32 state, mask;

	state = readl(zynq_slcr_base + SLCR_REBOOT_STATUS_OFFSET);
	mask = 1 << (31 - cpu);
	if (die)
		state |= mask;
	else
		state &= ~mask;
	writel(state, zynq_slcr_base + SLCR_REBOOT_STATUS_OFFSET);
}