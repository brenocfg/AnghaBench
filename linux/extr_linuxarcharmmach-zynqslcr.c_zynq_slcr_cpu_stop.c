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
 int SLCR_A9_CPU_CLKSTOP ; 
 int SLCR_A9_CPU_RST ; 
 int /*<<< orphan*/  SLCR_A9_CPU_RST_CTRL_OFFSET ; 
 int /*<<< orphan*/  zynq_slcr_read (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_slcr_write (int,int /*<<< orphan*/ ) ; 

void zynq_slcr_cpu_stop(int cpu)
{
	u32 reg;

	zynq_slcr_read(&reg, SLCR_A9_CPU_RST_CTRL_OFFSET);
	reg |= (SLCR_A9_CPU_CLKSTOP | SLCR_A9_CPU_RST) << cpu;
	zynq_slcr_write(reg, SLCR_A9_CPU_RST_CTRL_OFFSET);
}