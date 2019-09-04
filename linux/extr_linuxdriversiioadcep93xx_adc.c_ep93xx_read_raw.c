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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int address; int /*<<< orphan*/  channel; } ;
struct ep93xx_adc_priv {int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  lastch; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 scalar_t__ EP93XX_ADC_RESULT ; 
 int EP93XX_ADC_SDR ; 
 scalar_t__ EP93XX_ADC_SWITCH ; 
 scalar_t__ EP93XX_ADC_SW_LOCK ; 
 int ETIMEDOUT ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ep93xx_adc_delay (int,int) ; 
 struct ep93xx_adc_priv* iio_priv (struct iio_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl_relaxed (scalar_t__) ; 
 int sign_extend32 (int,int) ; 
 int /*<<< orphan*/  time_after (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int ep93xx_read_raw(struct iio_dev *iiodev,
			   struct iio_chan_spec const *channel, int *value,
			   int *shift, long mask)
{
	struct ep93xx_adc_priv *priv = iio_priv(iiodev);
	unsigned long timeout;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&priv->lock);
		if (priv->lastch != channel->channel) {
			priv->lastch = channel->channel;
			/*
			 * Switch register is software-locked, unlocking must be
			 * immediately followed by write
			 */
			local_irq_disable();
			writel_relaxed(0xAA, priv->base + EP93XX_ADC_SW_LOCK);
			writel_relaxed(channel->address,
				       priv->base + EP93XX_ADC_SWITCH);
			local_irq_enable();
			/*
			 * Settling delay depends on module clock and could be
			 * 2ms or 500us
			 */
			ep93xx_adc_delay(2000, 2000);
		}
		/* Start the conversion, eventually discarding old result */
		readl_relaxed(priv->base + EP93XX_ADC_RESULT);
		/* Ensure maximum conversion rate is not exceeded */
		ep93xx_adc_delay(DIV_ROUND_UP(1000000, 925),
				 DIV_ROUND_UP(1000000, 925));
		/* At this point conversion must be completed, but anyway... */
		ret = IIO_VAL_INT;
		timeout = jiffies + msecs_to_jiffies(1) + 1;
		while (1) {
			u32 t;

			t = readl_relaxed(priv->base + EP93XX_ADC_RESULT);
			if (t & EP93XX_ADC_SDR) {
				*value = sign_extend32(t, 15);
				break;
			}

			if (time_after(jiffies, timeout)) {
				dev_err(&iiodev->dev, "Conversion timeout\n");
				ret = -ETIMEDOUT;
				break;
			}

			cpu_relax();
		}
		mutex_unlock(&priv->lock);
		return ret;

	case IIO_CHAN_INFO_OFFSET:
		/* According to datasheet, range is -25000..25000 */
		*value = 25000;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		/* Typical supply voltage is 3.3v */
		*value = (1ULL << 32) * 3300 / 50000;
		*shift = 32;
		return IIO_VAL_FRACTIONAL_LOG2;
	}

	return -EINVAL;
}