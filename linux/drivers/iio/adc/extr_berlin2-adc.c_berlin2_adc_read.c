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
struct iio_dev {int dummy; } ;
struct berlin2_adc_priv {int data_available; int data; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BERLIN2_SM_ADC_STATUS ; 
 int BERLIN2_SM_ADC_STATUS_INT_EN (int) ; 
 int /*<<< orphan*/  BERLIN2_SM_CTRL ; 
 int BERLIN2_SM_CTRL_ADC_RESET ; 
 int BERLIN2_SM_CTRL_ADC_SEL (int) ; 
 int BERLIN2_SM_CTRL_ADC_SEL_MASK ; 
 int BERLIN2_SM_CTRL_ADC_START ; 
 int ETIMEDOUT ; 
 struct berlin2_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int berlin2_adc_read(struct iio_dev *indio_dev, int channel)
{
	struct berlin2_adc_priv *priv = iio_priv(indio_dev);
	int data, ret;

	mutex_lock(&priv->lock);

	/* Enable the interrupts */
	regmap_write(priv->regmap, BERLIN2_SM_ADC_STATUS,
		     BERLIN2_SM_ADC_STATUS_INT_EN(channel));

	/* Configure the ADC */
	regmap_update_bits(priv->regmap, BERLIN2_SM_CTRL,
			   BERLIN2_SM_CTRL_ADC_RESET |
			   BERLIN2_SM_CTRL_ADC_SEL_MASK |
			   BERLIN2_SM_CTRL_ADC_START,
			   BERLIN2_SM_CTRL_ADC_SEL(channel) |
			   BERLIN2_SM_CTRL_ADC_START);

	ret = wait_event_interruptible_timeout(priv->wq, priv->data_available,
					       msecs_to_jiffies(1000));

	/* Disable the interrupts */
	regmap_update_bits(priv->regmap, BERLIN2_SM_ADC_STATUS,
			   BERLIN2_SM_ADC_STATUS_INT_EN(channel), 0);

	if (ret == 0)
		ret = -ETIMEDOUT;
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}

	regmap_update_bits(priv->regmap, BERLIN2_SM_CTRL,
			   BERLIN2_SM_CTRL_ADC_START, 0);

	data = priv->data;
	priv->data_available = false;

	mutex_unlock(&priv->lock);

	return data;
}