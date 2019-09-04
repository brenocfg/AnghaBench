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
struct iproc_ts_priv {int /*<<< orphan*/  tsc_clk; int /*<<< orphan*/  regmap; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERRUPT_MASK ; 
 int /*<<< orphan*/  REGCTL2 ; 
 int TS_CONTROLLER_PWR_TS ; 
 int TS_FIFO_INTR_MASK ; 
 int TS_PEN_INTR_MASK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct iproc_ts_priv* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void iproc_ts_stop(struct input_dev *dev)
{
	u32 val;
	struct iproc_ts_priv *priv = input_get_drvdata(dev);

	/*
	 * Disable FIFO int_th and pen event(up/down)Interrupts only
	 * as the interrupt mask register is shared between ADC, TS and
	 * flextimer.
	 */
	val = TS_PEN_INTR_MASK | TS_FIFO_INTR_MASK;
	regmap_update_bits(priv->regmap, INTERRUPT_MASK, val, 0);

	/* Only power down touch screen controller */
	val = TS_CONTROLLER_PWR_TS;
	regmap_update_bits(priv->regmap, REGCTL2, val, val);

	clk_disable(priv->tsc_clk);
}