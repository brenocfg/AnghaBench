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
struct mx25_tcq_priv {int /*<<< orphan*/  regs; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  MX25_ADCQ_SR ; 
 int MX25_ADCQ_SR_FDRY ; 
 int MX25_ADCQ_SR_FOR ; 
 int MX25_ADCQ_SR_FRR ; 
 int MX25_ADCQ_SR_FUR ; 
 int MX25_ADCQ_SR_PD ; 
 int /*<<< orphan*/  mx25_tcq_disable_fifo_irq (struct mx25_tcq_priv*) ; 
 int /*<<< orphan*/  mx25_tcq_disable_touch_irq (struct mx25_tcq_priv*) ; 
 int /*<<< orphan*/  mx25_tcq_enable_fifo_irq (struct mx25_tcq_priv*) ; 
 int /*<<< orphan*/  mx25_tcq_force_queue_start (struct mx25_tcq_priv*) ; 
 int /*<<< orphan*/  mx25_tcq_re_enable_touch_detection (struct mx25_tcq_priv*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t mx25_tcq_irq(int irq, void *dev_id)
{
	struct mx25_tcq_priv *priv = dev_id;
	u32 stat;
	int ret = IRQ_HANDLED;

	regmap_read(priv->regs, MX25_ADCQ_SR, &stat);

	if (stat & (MX25_ADCQ_SR_FRR | MX25_ADCQ_SR_FUR | MX25_ADCQ_SR_FOR))
		mx25_tcq_re_enable_touch_detection(priv);

	if (stat & MX25_ADCQ_SR_PD) {
		mx25_tcq_disable_touch_irq(priv);
		mx25_tcq_force_queue_start(priv);
		mx25_tcq_enable_fifo_irq(priv);
	}

	if (stat & MX25_ADCQ_SR_FDRY) {
		mx25_tcq_disable_fifo_irq(priv);
		ret = IRQ_WAKE_THREAD;
	}

	regmap_update_bits(priv->regs, MX25_ADCQ_SR, MX25_ADCQ_SR_FRR |
			   MX25_ADCQ_SR_FUR | MX25_ADCQ_SR_FOR |
			   MX25_ADCQ_SR_PD,
			   MX25_ADCQ_SR_FRR | MX25_ADCQ_SR_FUR |
			   MX25_ADCQ_SR_FOR | MX25_ADCQ_SR_PD);

	return ret;
}