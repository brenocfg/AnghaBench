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
 scalar_t__ zynq_slcr_base ; 

bool zynq_slcr_cpu_state_read(int cpu)
{
	u32 state;

	state = readl(zynq_slcr_base + SLCR_REBOOT_STATUS_OFFSET);
	state &= 1 << (31 - cpu);

	return !state;
}