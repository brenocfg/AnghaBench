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
struct ir_raw_event {int pulse; void* duration; } ;
struct hix5hd2_ir_priv {int /*<<< orphan*/  rdev; scalar_t__ base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int INTMS_OVERFLOW ; 
 int INTMS_SYMBRCV ; 
 int INTMS_TIMEOUT ; 
 int /*<<< orphan*/  INT_CLR_OVERFLOW ; 
 int /*<<< orphan*/  INT_CLR_RCV ; 
 int /*<<< orphan*/  INT_CLR_TIMEOUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IR_CFG_INT_THRESHOLD ; 
 int IR_CFG_SYMBOL_MAXWIDTH ; 
 scalar_t__ IR_DATAH ; 
 scalar_t__ IR_DATAL ; 
 scalar_t__ IR_INTC ; 
 scalar_t__ IR_INTS ; 
 void* US_TO_NS (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_set_idle (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ir_raw_event_store (int /*<<< orphan*/ ,struct ir_raw_event*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t hix5hd2_ir_rx_interrupt(int irq, void *data)
{
	u32 symb_num, symb_val, symb_time;
	u32 data_l, data_h;
	u32 irq_sr, i;
	struct hix5hd2_ir_priv *priv = data;

	irq_sr = readl_relaxed(priv->base + IR_INTS);
	if (irq_sr & INTMS_OVERFLOW) {
		/*
		 * we must read IR_DATAL first, then we can clean up
		 * IR_INTS availably since logic would not clear
		 * fifo when overflow, drv do the job
		 */
		ir_raw_event_reset(priv->rdev);
		symb_num = readl_relaxed(priv->base + IR_DATAH);
		for (i = 0; i < symb_num; i++)
			readl_relaxed(priv->base + IR_DATAL);

		writel_relaxed(INT_CLR_OVERFLOW, priv->base + IR_INTC);
		dev_info(priv->dev, "overflow, level=%d\n",
			 IR_CFG_INT_THRESHOLD);
	}

	if ((irq_sr & INTMS_SYMBRCV) || (irq_sr & INTMS_TIMEOUT)) {
		struct ir_raw_event ev = {};

		symb_num = readl_relaxed(priv->base + IR_DATAH);
		for (i = 0; i < symb_num; i++) {
			symb_val = readl_relaxed(priv->base + IR_DATAL);
			data_l = ((symb_val & 0xffff) * 10);
			data_h =  ((symb_val >> 16) & 0xffff) * 10;
			symb_time = (data_l + data_h) / 10;

			ev.duration = US_TO_NS(data_l);
			ev.pulse = true;
			ir_raw_event_store(priv->rdev, &ev);

			if (symb_time < IR_CFG_SYMBOL_MAXWIDTH) {
				ev.duration = US_TO_NS(data_h);
				ev.pulse = false;
				ir_raw_event_store(priv->rdev, &ev);
			} else {
				ir_raw_event_set_idle(priv->rdev, true);
			}
		}

		if (irq_sr & INTMS_SYMBRCV)
			writel_relaxed(INT_CLR_RCV, priv->base + IR_INTC);
		if (irq_sr & INTMS_TIMEOUT)
			writel_relaxed(INT_CLR_TIMEOUT, priv->base + IR_INTC);
	}

	/* Empty software fifo */
	ir_raw_event_handle(priv->rdev);
	return IRQ_HANDLED;
}