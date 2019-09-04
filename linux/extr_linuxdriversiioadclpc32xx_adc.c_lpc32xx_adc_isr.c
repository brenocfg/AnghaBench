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
struct lpc32xx_adc_state {int value; int /*<<< orphan*/  completion; int /*<<< orphan*/  adc_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LPC32XXAD_VALUE (int /*<<< orphan*/ ) ; 
 int LPC32XXAD_VALUE_MASK ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t lpc32xx_adc_isr(int irq, void *dev_id)
{
	struct lpc32xx_adc_state *st = dev_id;

	/* Read value and clear irq */
	st->value = __raw_readl(LPC32XXAD_VALUE(st->adc_base)) &
		LPC32XXAD_VALUE_MASK;
	complete(&st->completion);

	return IRQ_HANDLED;
}