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
struct meson_sar_adc_priv {int /*<<< orphan*/  temperature_sensor_calibrated; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;
struct iio_chan_spec {scalar_t__ type; int /*<<< orphan*/  address; } ;
typedef  enum meson_sar_adc_num_samples { ____Placeholder_meson_sar_adc_num_samples } meson_sar_adc_num_samples ;
typedef  enum meson_sar_adc_avg_mode { ____Placeholder_meson_sar_adc_avg_mode } meson_sar_adc_avg_mode ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ IIO_TEMP ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  meson_sar_adc_clear_fifo (struct iio_dev*) ; 
 int /*<<< orphan*/  meson_sar_adc_enable_channel (struct iio_dev*,struct iio_chan_spec const*) ; 
 int meson_sar_adc_lock (struct iio_dev*) ; 
 int meson_sar_adc_read_raw_sample (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 int /*<<< orphan*/  meson_sar_adc_set_averaging (struct iio_dev*,struct iio_chan_spec const*,int,int) ; 
 int /*<<< orphan*/  meson_sar_adc_start_sample_engine (struct iio_dev*) ; 
 int /*<<< orphan*/  meson_sar_adc_stop_sample_engine (struct iio_dev*) ; 
 int /*<<< orphan*/  meson_sar_adc_unlock (struct iio_dev*) ; 

__attribute__((used)) static int meson_sar_adc_get_sample(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum meson_sar_adc_avg_mode avg_mode,
				    enum meson_sar_adc_num_samples avg_samples,
				    int *val)
{
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);
	int ret;

	if (chan->type == IIO_TEMP && !priv->temperature_sensor_calibrated)
		return -ENOTSUPP;

	ret = meson_sar_adc_lock(indio_dev);
	if (ret)
		return ret;

	/* clear the FIFO to make sure we're not reading old values */
	meson_sar_adc_clear_fifo(indio_dev);

	meson_sar_adc_set_averaging(indio_dev, chan, avg_mode, avg_samples);

	meson_sar_adc_enable_channel(indio_dev, chan);

	meson_sar_adc_start_sample_engine(indio_dev);
	ret = meson_sar_adc_read_raw_sample(indio_dev, chan, val);
	meson_sar_adc_stop_sample_engine(indio_dev);

	meson_sar_adc_unlock(indio_dev);

	if (ret) {
		dev_warn(indio_dev->dev.parent,
			 "failed to read sample for channel %lu: %d\n",
			 chan->address, ret);
		return ret;
	}

	return IIO_VAL_INT;
}