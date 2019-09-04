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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ address; } ;
struct aspeed_adc_model_data {int vref_voltage; } ;
struct aspeed_adc_data {TYPE_1__* clk_scaler; scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ASPEED_CLOCKS_PER_SAMPLE ; 
 int ASPEED_RESOLUTION_BITS ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct aspeed_adc_data* iio_priv (struct iio_dev*) ; 
 struct aspeed_adc_model_data* of_device_get_match_data (int /*<<< orphan*/ ) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static int aspeed_adc_read_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int *val, int *val2, long mask)
{
	struct aspeed_adc_data *data = iio_priv(indio_dev);
	const struct aspeed_adc_model_data *model_data =
			of_device_get_match_data(data->dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		*val = readw(data->base + chan->address);
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = model_data->vref_voltage;
		*val2 = ASPEED_RESOLUTION_BITS;
		return IIO_VAL_FRACTIONAL_LOG2;

	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = clk_get_rate(data->clk_scaler->clk) /
				ASPEED_CLOCKS_PER_SAMPLE;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}