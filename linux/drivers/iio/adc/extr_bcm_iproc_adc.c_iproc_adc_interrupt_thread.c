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
struct iproc_adc_priv {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int IPROC_ADC_INTR ; 
 int IPROC_ADC_INTR_MASK ; 
 int /*<<< orphan*/  IPROC_INTERRUPT_MASK ; 
 int /*<<< orphan*/  IPROC_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 struct iproc_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t iproc_adc_interrupt_thread(int irq, void *data)
{
	u32 channel_intr_status;
	u32 intr_status;
	u32 intr_mask;
	struct iio_dev *indio_dev = data;
	struct iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	/*
	 * This interrupt is shared with the touchscreen driver.
	 * Make sure this interrupt is intended for us.
	 * Handle only ADC channel specific interrupts.
	 */
	regmap_read(adc_priv->regmap, IPROC_INTERRUPT_STATUS, &intr_status);
	regmap_read(adc_priv->regmap, IPROC_INTERRUPT_MASK, &intr_mask);
	intr_status = intr_status & intr_mask;
	channel_intr_status = (intr_status & IPROC_ADC_INTR_MASK) >>
				IPROC_ADC_INTR;
	if (channel_intr_status)
		return IRQ_WAKE_THREAD;

	return IRQ_NONE;
}