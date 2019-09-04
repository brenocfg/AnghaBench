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
 int /*<<< orphan*/  AUX_IENABLE ; 
 int /*<<< orphan*/  AUX_IRQ_LEV ; 
 int /*<<< orphan*/  CONFIG_ARC_COMPACT_IRQ_LEVELS ; 
 unsigned int IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int NR_CPU_IRQS ; 
 unsigned int TIMER0_IRQ ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 unsigned int read_aux_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,unsigned int) ; 

void arc_init_IRQ(void)
{
	unsigned int level_mask = 0, i;

       /* Is timer high priority Interrupt (Level2 in ARCompact jargon) */
	level_mask |= IS_ENABLED(CONFIG_ARC_COMPACT_IRQ_LEVELS) << TIMER0_IRQ;

	/*
	 * Write to register, even if no LV2 IRQs configured to reset it
	 * in case bootloader had mucked with it
	 */
	write_aux_reg(AUX_IRQ_LEV, level_mask);

	if (level_mask)
		pr_info("Level-2 interrupts bitset %x\n", level_mask);

	/*
	 * Disable all IRQ lines so faulty external hardware won't
	 * trigger interrupt that kernel is not ready to handle.
	 */
	for (i = TIMER0_IRQ; i < NR_CPU_IRQS; i++) {
		unsigned int ienb;

		ienb = read_aux_reg(AUX_IENABLE);
		ienb &= ~(1 << i);
		write_aux_reg(AUX_IENABLE, ienb);
	}
}