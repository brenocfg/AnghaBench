#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {char sign; } ;
struct iio_chan_spec {scalar_t__ type; int /*<<< orphan*/  channel; TYPE_1__ scan_type; int /*<<< orphan*/  channel2; scalar_t__ differential; } ;
struct at91_adc_state {int conversion_done; int conversion_value; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq_data_available; struct iio_chan_spec const* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SAMA5D2_CHDR ; 
 int /*<<< orphan*/  AT91_SAMA5D2_CHER ; 
 int /*<<< orphan*/  AT91_SAMA5D2_COR ; 
 int AT91_SAMA5D2_COR_DIFF_OFFSET ; 
 int /*<<< orphan*/  AT91_SAMA5D2_CR ; 
 int AT91_SAMA5D2_CR_START ; 
 int /*<<< orphan*/  AT91_SAMA5D2_IDR ; 
 int /*<<< orphan*/  AT91_SAMA5D2_IER ; 
 int /*<<< orphan*/  AT91_SAMA5D2_LCDR ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 scalar_t__ IIO_POSITIONRELATIVE ; 
 scalar_t__ IIO_PRESSURE ; 
 int at91_adc_adjust_val_osr (struct at91_adc_state*,int*) ; 
 int at91_adc_read_position (struct at91_adc_state*,int /*<<< orphan*/ ,int*) ; 
 int at91_adc_read_pressure (struct at91_adc_state*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,int) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at91_adc_read_info_raw(struct iio_dev *indio_dev,
				  struct iio_chan_spec const *chan, int *val)
{
	struct at91_adc_state *st = iio_priv(indio_dev);
	u32 cor = 0;
	u16 tmp_val;
	int ret;

	/*
	 * Keep in mind that we cannot use software trigger or touchscreen
	 * if external trigger is enabled
	 */
	if (chan->type == IIO_POSITIONRELATIVE) {
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;
		mutex_lock(&st->lock);

		ret = at91_adc_read_position(st, chan->channel,
					     &tmp_val);
		*val = tmp_val;
		mutex_unlock(&st->lock);
		iio_device_release_direct_mode(indio_dev);

		return at91_adc_adjust_val_osr(st, val);
	}
	if (chan->type == IIO_PRESSURE) {
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;
		mutex_lock(&st->lock);

		ret = at91_adc_read_pressure(st, chan->channel,
					     &tmp_val);
		*val = tmp_val;
		mutex_unlock(&st->lock);
		iio_device_release_direct_mode(indio_dev);

		return at91_adc_adjust_val_osr(st, val);
	}

	/* in this case we have a voltage channel */

	ret = iio_device_claim_direct_mode(indio_dev);
	if (ret)
		return ret;
	mutex_lock(&st->lock);

	st->chan = chan;

	if (chan->differential)
		cor = (BIT(chan->channel) | BIT(chan->channel2)) <<
		      AT91_SAMA5D2_COR_DIFF_OFFSET;

	at91_adc_writel(st, AT91_SAMA5D2_COR, cor);
	at91_adc_writel(st, AT91_SAMA5D2_CHER, BIT(chan->channel));
	at91_adc_writel(st, AT91_SAMA5D2_IER, BIT(chan->channel));
	at91_adc_writel(st, AT91_SAMA5D2_CR, AT91_SAMA5D2_CR_START);

	ret = wait_event_interruptible_timeout(st->wq_data_available,
					       st->conversion_done,
					       msecs_to_jiffies(1000));
	if (ret == 0)
		ret = -ETIMEDOUT;

	if (ret > 0) {
		*val = st->conversion_value;
		ret = at91_adc_adjust_val_osr(st, val);
		if (chan->scan_type.sign == 's')
			*val = sign_extend32(*val, 11);
		st->conversion_done = false;
	}

	at91_adc_writel(st, AT91_SAMA5D2_IDR, BIT(chan->channel));
	at91_adc_writel(st, AT91_SAMA5D2_CHDR, BIT(chan->channel));

	/* Needed to ACK the DRDY interruption */
	at91_adc_readl(st, AT91_SAMA5D2_LCDR);

	mutex_unlock(&st->lock);

	iio_device_release_direct_mode(indio_dev);
	return ret;
}