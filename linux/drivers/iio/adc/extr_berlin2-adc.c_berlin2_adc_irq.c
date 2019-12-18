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
struct berlin2_adc_priv {unsigned int data; int data_available; int /*<<< orphan*/  wq; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BERLIN2_SM_ADC_DATA ; 
 unsigned int BERLIN2_SM_ADC_MASK ; 
 int /*<<< orphan*/  BERLIN2_SM_ADC_STATUS ; 
 unsigned int BERLIN2_SM_ADC_STATUS_DATA_RDY_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct berlin2_adc_priv* iio_priv (void*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t berlin2_adc_irq(int irq, void *private)
{
	struct berlin2_adc_priv *priv = iio_priv(private);
	unsigned val;

	regmap_read(priv->regmap, BERLIN2_SM_ADC_STATUS, &val);
	if (val & BERLIN2_SM_ADC_STATUS_DATA_RDY_MASK) {
		regmap_read(priv->regmap, BERLIN2_SM_ADC_DATA, &priv->data);
		priv->data &= BERLIN2_SM_ADC_MASK;

		val &= ~BERLIN2_SM_ADC_STATUS_DATA_RDY_MASK;
		regmap_write(priv->regmap, BERLIN2_SM_ADC_STATUS, val);

		priv->data_available = true;
		wake_up_interruptible(&priv->wq);
	}

	return IRQ_HANDLED;
}