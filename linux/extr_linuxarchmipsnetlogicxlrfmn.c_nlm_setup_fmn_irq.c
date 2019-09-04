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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_FMN ; 
 int /*<<< orphan*/  fmn_irqaction ; 
 int /*<<< orphan*/  nlm_cop2_disable_irqrestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_cop2_enable_irqsave () ; 
 int /*<<< orphan*/  nlm_fmn_setup_intr (int /*<<< orphan*/ ,int) ; 
 int nlm_threads_per_core ; 
 int /*<<< orphan*/  setup_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nlm_setup_fmn_irq(void)
{
	uint32_t flags;

	/* setup irq only once */
	setup_irq(IRQ_FMN, &fmn_irqaction);

	flags = nlm_cop2_enable_irqsave();
	nlm_fmn_setup_intr(IRQ_FMN, (1 << nlm_threads_per_core) - 1);
	nlm_cop2_disable_irqrestore(flags);
}