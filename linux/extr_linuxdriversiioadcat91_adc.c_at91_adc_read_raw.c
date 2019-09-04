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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  channel; } ;
struct at91_adc_state {int done; int last_value; int vref_mv; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq_data_avail; int /*<<< orphan*/  chnb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_ADC_CH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91_ADC_CHDR ; 
 int /*<<< orphan*/  AT91_ADC_CHER ; 
 int /*<<< orphan*/  AT91_ADC_CR ; 
 int /*<<< orphan*/  AT91_ADC_IDR ; 
 int /*<<< orphan*/  AT91_ADC_IER ; 
 int /*<<< orphan*/  AT91_ADC_START ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at91_adc_read_raw(struct iio_dev *idev,
			     struct iio_chan_spec const *chan,
			     int *val, int *val2, long mask)
{
	struct at91_adc_state *st = iio_priv(idev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);

		st->chnb = chan->channel;
		at91_adc_writel(st, AT91_ADC_CHER,
				AT91_ADC_CH(chan->channel));
		at91_adc_writel(st, AT91_ADC_IER, BIT(chan->channel));
		at91_adc_writel(st, AT91_ADC_CR, AT91_ADC_START);

		ret = wait_event_interruptible_timeout(st->wq_data_avail,
						       st->done,
						       msecs_to_jiffies(1000));

		/* Disable interrupts, regardless if adc conversion was
		 * successful or not
		 */
		at91_adc_writel(st, AT91_ADC_CHDR,
				AT91_ADC_CH(chan->channel));
		at91_adc_writel(st, AT91_ADC_IDR, BIT(chan->channel));

		if (ret > 0) {
			/* a valid conversion took place */
			*val = st->last_value;
			st->last_value = 0;
			st->done = false;
			ret = IIO_VAL_INT;
		} else if (ret == 0) {
			/* conversion timeout */
			dev_err(&idev->dev, "ADC Channel %d timeout.\n",
				chan->channel);
			ret = -ETIMEDOUT;
		}

		mutex_unlock(&st->lock);
		return ret;

	case IIO_CHAN_INFO_SCALE:
		*val = st->vref_mv;
		*val2 = chan->scan_type.realbits;
		return IIO_VAL_FRACTIONAL_LOG2;
	default:
		break;
	}
	return -EINVAL;
}