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
struct meson_sar_adc_priv {TYPE_1__* param; int /*<<< orphan*/  regmap; int /*<<< orphan*/  done; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int address; } ;
struct TYPE_2__ {scalar_t__ resolution; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MESON_SAR_ADC_FIFO_RD ; 
 int /*<<< orphan*/  MESON_SAR_ADC_FIFO_RD_CHAN_ID_MASK ; 
 int /*<<< orphan*/  MESON_SAR_ADC_FIFO_RD_SAMPLE_VALUE_MASK ; 
 int /*<<< orphan*/  MESON_SAR_ADC_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int meson_sar_adc_calib_val (struct iio_dev*,int) ; 
 int meson_sar_adc_get_fifo_count (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_sar_adc_read_raw_sample(struct iio_dev *indio_dev,
					 const struct iio_chan_spec *chan,
					 int *val)
{
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);
	int regval, fifo_chan, fifo_val, count;

	if(!wait_for_completion_timeout(&priv->done,
				msecs_to_jiffies(MESON_SAR_ADC_TIMEOUT)))
		return -ETIMEDOUT;

	count = meson_sar_adc_get_fifo_count(indio_dev);
	if (count != 1) {
		dev_err(&indio_dev->dev,
			"ADC FIFO has %d element(s) instead of one\n", count);
		return -EINVAL;
	}

	regmap_read(priv->regmap, MESON_SAR_ADC_FIFO_RD, &regval);
	fifo_chan = FIELD_GET(MESON_SAR_ADC_FIFO_RD_CHAN_ID_MASK, regval);
	if (fifo_chan != chan->address) {
		dev_err(&indio_dev->dev,
			"ADC FIFO entry belongs to channel %d instead of %lu\n",
			fifo_chan, chan->address);
		return -EINVAL;
	}

	fifo_val = FIELD_GET(MESON_SAR_ADC_FIFO_RD_SAMPLE_VALUE_MASK, regval);
	fifo_val &= GENMASK(priv->param->resolution - 1, 0);
	*val = meson_sar_adc_calib_val(indio_dev, fifo_val);

	return 0;
}