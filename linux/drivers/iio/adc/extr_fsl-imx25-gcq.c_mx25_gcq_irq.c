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
struct mx25_gcq_priv {int /*<<< orphan*/  regs; int /*<<< orphan*/  completed; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MX25_ADCQ_CR ; 
 int /*<<< orphan*/  MX25_ADCQ_CR_FQS ; 
 int /*<<< orphan*/  MX25_ADCQ_MR ; 
 int /*<<< orphan*/  MX25_ADCQ_MR_EOQ_IRQ ; 
 int /*<<< orphan*/  MX25_ADCQ_SR ; 
 int MX25_ADCQ_SR_EOQ ; 
 int MX25_ADCQ_SR_FOR ; 
 int MX25_ADCQ_SR_FRR ; 
 int MX25_ADCQ_SR_FUR ; 
 int MX25_ADCQ_SR_PD ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t mx25_gcq_irq(int irq, void *data)
{
	struct mx25_gcq_priv *priv = data;
	u32 stats;

	regmap_read(priv->regs, MX25_ADCQ_SR, &stats);

	if (stats & MX25_ADCQ_SR_EOQ) {
		regmap_update_bits(priv->regs, MX25_ADCQ_MR,
				   MX25_ADCQ_MR_EOQ_IRQ, MX25_ADCQ_MR_EOQ_IRQ);
		complete(&priv->completed);
	}

	/* Disable conversion queue run */
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_FQS, 0);

	/* Acknowledge all possible irqs */
	regmap_write(priv->regs, MX25_ADCQ_SR, MX25_ADCQ_SR_FRR |
		     MX25_ADCQ_SR_FUR | MX25_ADCQ_SR_FOR |
		     MX25_ADCQ_SR_EOQ | MX25_ADCQ_SR_PD);

	return IRQ_HANDLED;
}