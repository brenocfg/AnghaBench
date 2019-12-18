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
struct imx6ul_tsc {int /*<<< orphan*/  input; int /*<<< orphan*/  xnur_gpio; scalar_t__ tsc_regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int DETECT_SIGNAL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MEASURE_SIGNAL ; 
 scalar_t__ REG_TSC_FLOW_CONTROL ; 
 scalar_t__ REG_TSC_INT_STATUS ; 
 scalar_t__ REG_TSC_MEASURE_VALUE ; 
 int START_SENSE ; 
 scalar_t__ gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  tsc_wait_detect_mode (struct imx6ul_tsc*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t tsc_irq_fn(int irq, void *dev_id)
{
	struct imx6ul_tsc *tsc = dev_id;
	u32 status;
	u32 value;
	u32 x, y;
	u32 start;

	status = readl(tsc->tsc_regs + REG_TSC_INT_STATUS);

	/* write 1 to clear the bit measure-signal */
	writel(MEASURE_SIGNAL | DETECT_SIGNAL,
		tsc->tsc_regs + REG_TSC_INT_STATUS);

	/* It's a HW self-clean bit. Set this bit and start sense detection */
	start = readl(tsc->tsc_regs + REG_TSC_FLOW_CONTROL);
	start |= START_SENSE;
	writel(start, tsc->tsc_regs + REG_TSC_FLOW_CONTROL);

	if (status & MEASURE_SIGNAL) {
		value = readl(tsc->tsc_regs + REG_TSC_MEASURE_VALUE);
		x = (value >> 16) & 0x0fff;
		y = value & 0x0fff;

		/*
		 * In detect mode, we can get the xnur gpio value,
		 * otherwise assume contact is stiull active.
		 */
		if (!tsc_wait_detect_mode(tsc) ||
		    gpiod_get_value_cansleep(tsc->xnur_gpio)) {
			input_report_key(tsc->input, BTN_TOUCH, 1);
			input_report_abs(tsc->input, ABS_X, x);
			input_report_abs(tsc->input, ABS_Y, y);
		} else {
			input_report_key(tsc->input, BTN_TOUCH, 0);
		}

		input_sync(tsc->input);
	}

	return IRQ_HANDLED;
}