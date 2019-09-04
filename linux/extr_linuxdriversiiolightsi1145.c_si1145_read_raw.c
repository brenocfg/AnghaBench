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
typedef  int /*<<< orphan*/  u8 ;
struct si1145_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  channel2; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 137 
#define  IIO_CHAN_INFO_RAW 136 
#define  IIO_CHAN_INFO_SAMP_FREQ 135 
#define  IIO_CHAN_INFO_SCALE 134 
#define  IIO_CURRENT 133 
#define  IIO_INTENSITY 132 
 int /*<<< orphan*/  IIO_MOD_LIGHT_IR ; 
#define  IIO_PROXIMITY 131 
#define  IIO_TEMP 130 
#define  IIO_UVINDEX 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
#define  IIO_VOLTAGE 128 
 int /*<<< orphan*/  SI1145_PARAM_ADC_OFFSET ; 
 int /*<<< orphan*/  SI1145_PARAM_ALSIR_ADC_GAIN ; 
 int /*<<< orphan*/  SI1145_PARAM_ALSVIS_ADC_GAIN ; 
 int /*<<< orphan*/  SI1145_PARAM_PS_ADC_GAIN ; 
 int /*<<< orphan*/  SI1145_PS_LED_REG (int /*<<< orphan*/ ) ; 
 int SI1145_PS_LED_SHIFT (int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct si1145_data* iio_priv (struct iio_dev*) ; 
 int si1145_measure (struct iio_dev*,struct iio_chan_spec const*) ; 
 int si1145_param_query (struct si1145_data*,int /*<<< orphan*/ ) ; 
 int si1145_read_samp_freq (struct si1145_data*,int*,int*) ; 
 int si1145_scale_from_adcgain (int) ; 
 int si1145_uncompress (int) ; 

__attribute__((used)) static int si1145_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct si1145_data *data = iio_priv(indio_dev);
	int ret;
	u8 reg;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_PROXIMITY:
		case IIO_VOLTAGE:
		case IIO_TEMP:
		case IIO_UVINDEX:
			ret = iio_device_claim_direct_mode(indio_dev);
			if (ret)
				return ret;
			ret = si1145_measure(indio_dev, chan);
			iio_device_release_direct_mode(indio_dev);

			if (ret < 0)
				return ret;

			*val = ret;

			return IIO_VAL_INT;
		case IIO_CURRENT:
			ret = i2c_smbus_read_byte_data(data->client,
				SI1145_PS_LED_REG(chan->channel));
			if (ret < 0)
				return ret;

			*val = (ret >> SI1145_PS_LED_SHIFT(chan->channel))
				& 0x0f;

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_PROXIMITY:
			reg = SI1145_PARAM_PS_ADC_GAIN;
			break;
		case IIO_INTENSITY:
			if (chan->channel2 == IIO_MOD_LIGHT_IR)
				reg = SI1145_PARAM_ALSIR_ADC_GAIN;
			else
				reg = SI1145_PARAM_ALSVIS_ADC_GAIN;
			break;
		case IIO_TEMP:
			*val = 28;
			*val2 = 571429;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_UVINDEX:
			*val = 0;
			*val2 = 10000;
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}

		ret = si1145_param_query(data, reg);
		if (ret < 0)
			return ret;

		*val = si1145_scale_from_adcgain(ret & 0x07);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			/*
			 * -ADC offset - ADC counts @ 25°C -
			 *   35 * ADC counts / °C
			 */
			*val = -256 - 11136 + 25 * 35;
			return IIO_VAL_INT;
		default:
			/*
			 * All ADC measurements have are by default offset
			 * by -256
			 * See AN498 5.6.3
			 */
			ret = si1145_param_query(data, SI1145_PARAM_ADC_OFFSET);
			if (ret < 0)
				return ret;
			*val = -si1145_uncompress(ret);
			return IIO_VAL_INT;
		}
	case IIO_CHAN_INFO_SAMP_FREQ:
		return si1145_read_samp_freq(data, val, val2);
	default:
		return -EINVAL;
	}
}