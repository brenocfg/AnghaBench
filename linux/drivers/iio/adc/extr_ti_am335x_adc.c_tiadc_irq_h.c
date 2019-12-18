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
struct tiadc_device {int dummy; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int CNTRLREG_TSCSSENB ; 
 unsigned int IRQENB_FIFO1OVRRUN ; 
 unsigned int IRQENB_FIFO1THRES ; 
 unsigned int IRQENB_FIFO1UNDRFLW ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  REG_ADCFSM ; 
 int /*<<< orphan*/  REG_CTRL ; 
 int /*<<< orphan*/  REG_IRQCLR ; 
 int /*<<< orphan*/  REG_IRQSTATUS ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 unsigned int tiadc_readl (struct tiadc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tiadc_writel (struct tiadc_device*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t tiadc_irq_h(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	unsigned int status, config, adc_fsm;
	unsigned short count = 0;

	status = tiadc_readl(adc_dev, REG_IRQSTATUS);

	/*
	 * ADC and touchscreen share the IRQ line.
	 * FIFO0 interrupts are used by TSC. Handle FIFO1 IRQs here only
	 */
	if (status & IRQENB_FIFO1OVRRUN) {
		/* FIFO Overrun. Clear flag. Disable/Enable ADC to recover */
		config = tiadc_readl(adc_dev, REG_CTRL);
		config &= ~(CNTRLREG_TSCSSENB);
		tiadc_writel(adc_dev, REG_CTRL, config);
		tiadc_writel(adc_dev, REG_IRQSTATUS, IRQENB_FIFO1OVRRUN
				| IRQENB_FIFO1UNDRFLW | IRQENB_FIFO1THRES);

		/* wait for idle state.
		 * ADC needs to finish the current conversion
		 * before disabling the module
		 */
		do {
			adc_fsm = tiadc_readl(adc_dev, REG_ADCFSM);
		} while (adc_fsm != 0x10 && count++ < 100);

		tiadc_writel(adc_dev, REG_CTRL, (config | CNTRLREG_TSCSSENB));
		return IRQ_HANDLED;
	} else if (status & IRQENB_FIFO1THRES) {
		/* Disable irq and wake worker thread */
		tiadc_writel(adc_dev, REG_IRQCLR, IRQENB_FIFO1THRES);
		return IRQ_WAKE_THREAD;
	}

	return IRQ_NONE;
}