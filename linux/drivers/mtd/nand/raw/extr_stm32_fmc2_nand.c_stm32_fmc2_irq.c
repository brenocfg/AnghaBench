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
struct stm32_fmc2_nfc {scalar_t__ irq_state; int /*<<< orphan*/  complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ FMC2_IRQ_BCH ; 
 scalar_t__ FMC2_IRQ_SEQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_fmc2_disable_bch_irq (struct stm32_fmc2_nfc*) ; 
 int /*<<< orphan*/  stm32_fmc2_disable_seq_irq (struct stm32_fmc2_nfc*) ; 

__attribute__((used)) static irqreturn_t stm32_fmc2_irq(int irq, void *dev_id)
{
	struct stm32_fmc2_nfc *fmc2 = (struct stm32_fmc2_nfc *)dev_id;

	if (fmc2->irq_state == FMC2_IRQ_SEQ)
		/* Sequencer is used */
		stm32_fmc2_disable_seq_irq(fmc2);
	else if (fmc2->irq_state == FMC2_IRQ_BCH)
		/* BCH is used */
		stm32_fmc2_disable_bch_irq(fmc2);

	complete(&fmc2->complete);

	return IRQ_HANDLED;
}