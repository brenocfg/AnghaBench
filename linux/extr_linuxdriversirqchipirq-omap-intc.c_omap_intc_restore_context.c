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
struct TYPE_2__ {int /*<<< orphan*/ * mir; int /*<<< orphan*/ * ilr; int /*<<< orphan*/  threshold; int /*<<< orphan*/  idle; int /*<<< orphan*/  protection; int /*<<< orphan*/  sysconfig; } ;

/* Variables and functions */
 int INTCPS_NR_MIR_REGS ; 
 scalar_t__ INTC_IDLE ; 
 scalar_t__ INTC_ILR0 ; 
 scalar_t__ INTC_MIR0 ; 
 scalar_t__ INTC_PROTECTION ; 
 scalar_t__ INTC_SYSCONFIG ; 
 scalar_t__ INTC_THRESHOLD ; 
 TYPE_1__ intc_context ; 
 int /*<<< orphan*/  intc_writel (scalar_t__,int /*<<< orphan*/ ) ; 
 int omap_nr_irqs ; 

void omap_intc_restore_context(void)
{
	int i;

	intc_writel(INTC_SYSCONFIG, intc_context.sysconfig);
	intc_writel(INTC_PROTECTION, intc_context.protection);
	intc_writel(INTC_IDLE, intc_context.idle);
	intc_writel(INTC_THRESHOLD, intc_context.threshold);

	for (i = 0; i < omap_nr_irqs; i++)
		intc_writel(INTC_ILR0 + 0x4 * i,
				intc_context.ilr[i]);

	for (i = 0; i < INTCPS_NR_MIR_REGS; i++)
		intc_writel(INTC_MIR0 + 0x20 * i,
			intc_context.mir[i]);
	/* MIRs are saved and restore with other PRCM registers */
}