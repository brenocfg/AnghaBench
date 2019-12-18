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
struct lpc32xx_tsc {struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int LPC32XX_TSC_ADCDAT_VALUE_MASK ; 
 int /*<<< orphan*/  LPC32XX_TSC_FIFO ; 
 int LPC32XX_TSC_FIFO_NORMALIZE_X_VAL (int) ; 
 int LPC32XX_TSC_FIFO_NORMALIZE_Y_VAL (int) ; 
 int LPC32XX_TSC_FIFO_TS_P_LEVEL ; 
 int /*<<< orphan*/  LPC32XX_TSC_STAT ; 
 int LPC32XX_TSC_STAT_FIFO_EMPTY ; 
 int LPC32XX_TSC_STAT_FIFO_OVRRN ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  lpc32xx_fifo_clear (struct lpc32xx_tsc*) ; 
 int tsc_readl (struct lpc32xx_tsc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lpc32xx_ts_interrupt(int irq, void *dev_id)
{
	u32 tmp, rv[4], xs[4], ys[4];
	int idx;
	struct lpc32xx_tsc *tsc = dev_id;
	struct input_dev *input = tsc->dev;

	tmp = tsc_readl(tsc, LPC32XX_TSC_STAT);

	if (tmp & LPC32XX_TSC_STAT_FIFO_OVRRN) {
		/* FIFO overflow - throw away samples */
		lpc32xx_fifo_clear(tsc);
		return IRQ_HANDLED;
	}

	/*
	 * Gather and normalize 4 samples. Pen-up events may have less
	 * than 4 samples, but its ok to pop 4 and let the last sample
	 * pen status check drop the samples.
	 */
	idx = 0;
	while (idx < 4 &&
	       !(tsc_readl(tsc, LPC32XX_TSC_STAT) &
			LPC32XX_TSC_STAT_FIFO_EMPTY)) {
		tmp = tsc_readl(tsc, LPC32XX_TSC_FIFO);
		xs[idx] = LPC32XX_TSC_ADCDAT_VALUE_MASK -
			LPC32XX_TSC_FIFO_NORMALIZE_X_VAL(tmp);
		ys[idx] = LPC32XX_TSC_ADCDAT_VALUE_MASK -
			LPC32XX_TSC_FIFO_NORMALIZE_Y_VAL(tmp);
		rv[idx] = tmp;
		idx++;
	}

	/* Data is only valid if pen is still down in last sample */
	if (!(rv[3] & LPC32XX_TSC_FIFO_TS_P_LEVEL) && idx == 4) {
		/* Use average of 2nd and 3rd sample for position */
		input_report_abs(input, ABS_X, (xs[1] + xs[2]) / 2);
		input_report_abs(input, ABS_Y, (ys[1] + ys[2]) / 2);
		input_report_key(input, BTN_TOUCH, 1);
	} else {
		input_report_key(input, BTN_TOUCH, 0);
	}

	input_sync(input);

	return IRQ_HANDLED;
}