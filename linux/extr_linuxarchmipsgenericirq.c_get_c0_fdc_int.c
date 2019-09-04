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

/* Variables and functions */
 int MIPS_CPU_IRQ_BASE ; 
 int cp0_fdc_irq ; 
 scalar_t__ cpu_has_veic ; 
 int gic_get_c0_fdc_int () ; 
 scalar_t__ mips_gic_present () ; 
 int /*<<< orphan*/  panic (char*) ; 

int get_c0_fdc_int(void)
{
	int mips_cpu_fdc_irq;

	if (mips_gic_present())
		mips_cpu_fdc_irq = gic_get_c0_fdc_int();
	else if (cpu_has_veic)
		panic("Unimplemented!");
	else if (cp0_fdc_irq >= 0)
		mips_cpu_fdc_irq = MIPS_CPU_IRQ_BASE + cp0_fdc_irq;
	else
		mips_cpu_fdc_irq = -1;

	return mips_cpu_fdc_irq;
}