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
struct titsc {int pen_down; unsigned int x_plate_resistance; int /*<<< orphan*/  step_mask; int /*<<< orphan*/  mfd_tscadc; int /*<<< orphan*/  dev; struct input_dev* input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 unsigned int ADCFSM_STEPID ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 unsigned int IRQENB_EOS ; 
 unsigned int IRQENB_FIFO0THRES ; 
 unsigned int IRQENB_HW_PEN ; 
 unsigned int IRQENB_PENUP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int MAX_12BIT ; 
 int /*<<< orphan*/  REG_ADCFSM ; 
 int /*<<< orphan*/  REG_IRQSTATUS ; 
 int /*<<< orphan*/  REG_RAWIRQSTATUS ; 
 int /*<<< orphan*/  am335x_tsc_se_set_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  pm_relax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_stay_awake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  titsc_read_coordinates (struct titsc*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 unsigned int titsc_readl (struct titsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  titsc_writel (struct titsc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t titsc_irq(int irq, void *dev)
{
	struct titsc *ts_dev = dev;
	struct input_dev *input_dev = ts_dev->input;
	unsigned int fsm, status, irqclr = 0;
	unsigned int x = 0, y = 0;
	unsigned int z1, z2, z;

	status = titsc_readl(ts_dev, REG_RAWIRQSTATUS);
	if (status & IRQENB_HW_PEN) {
		ts_dev->pen_down = true;
		irqclr |= IRQENB_HW_PEN;
		pm_stay_awake(ts_dev->dev);
	}

	if (status & IRQENB_PENUP) {
		fsm = titsc_readl(ts_dev, REG_ADCFSM);
		if (fsm == ADCFSM_STEPID) {
			ts_dev->pen_down = false;
			input_report_key(input_dev, BTN_TOUCH, 0);
			input_report_abs(input_dev, ABS_PRESSURE, 0);
			input_sync(input_dev);
			pm_relax(ts_dev->dev);
		} else {
			ts_dev->pen_down = true;
		}
		irqclr |= IRQENB_PENUP;
	}

	if (status & IRQENB_EOS)
		irqclr |= IRQENB_EOS;

	/*
	 * ADC and touchscreen share the IRQ line.
	 * FIFO1 interrupts are used by ADC. Handle FIFO0 IRQs here only
	 */
	if (status & IRQENB_FIFO0THRES) {

		titsc_read_coordinates(ts_dev, &x, &y, &z1, &z2);

		if (ts_dev->pen_down && z1 != 0 && z2 != 0) {
			/*
			 * Calculate pressure using formula
			 * Resistance(touch) = x plate resistance *
			 * x postion/4096 * ((z2 / z1) - 1)
			 */
			z = z1 - z2;
			z *= x;
			z *= ts_dev->x_plate_resistance;
			z /= z2;
			z = (z + 2047) >> 12;

			if (z <= MAX_12BIT) {
				input_report_abs(input_dev, ABS_X, x);
				input_report_abs(input_dev, ABS_Y, y);
				input_report_abs(input_dev, ABS_PRESSURE, z);
				input_report_key(input_dev, BTN_TOUCH, 1);
				input_sync(input_dev);
			}
		}
		irqclr |= IRQENB_FIFO0THRES;
	}
	if (irqclr) {
		titsc_writel(ts_dev, REG_IRQSTATUS, irqclr);
		if (status & IRQENB_EOS)
			am335x_tsc_se_set_cache(ts_dev->mfd_tscadc,
						ts_dev->step_mask);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}