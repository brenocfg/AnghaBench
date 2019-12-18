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
struct tmp007_data {int config; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel2; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_MOD_TEMP_AMBIENT 129 
#define  IIO_MOD_TEMP_OBJECT 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int TMP007_CONFIG_CR_MASK ; 
 int TMP007_CONFIG_CR_SHIFT ; 
 int /*<<< orphan*/  TMP007_TDIE ; 
 int TMP007_TEMP_SHIFT ; 
 int /*<<< orphan*/  TMP007_TOBJECT ; 
 int i2c_smbus_read_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tmp007_data* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int,int) ; 
 int** tmp007_avgs ; 
 int tmp007_read_temperature (struct tmp007_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tmp007_read_raw(struct iio_dev *indio_dev,
		struct iio_chan_spec const *channel, int *val,
		int *val2, long mask)
{
	struct tmp007_data *data = iio_priv(indio_dev);
	s32 ret;
	int conv_rate;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (channel->channel2) {
		case IIO_MOD_TEMP_AMBIENT: /* LSB: 0.03125 degree Celsius */
			ret = i2c_smbus_read_word_swapped(data->client, TMP007_TDIE);
			if (ret < 0)
				return ret;
			break;
		case IIO_MOD_TEMP_OBJECT:
			ret = tmp007_read_temperature(data, TMP007_TOBJECT);
			if (ret < 0)
				return ret;
			break;
		default:
			return -EINVAL;
		}

		*val = sign_extend32(ret, 15) >> TMP007_TEMP_SHIFT;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 31;
		*val2 = 250000;

		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		conv_rate = (data->config & TMP007_CONFIG_CR_MASK)
				>> TMP007_CONFIG_CR_SHIFT;
		*val = tmp007_avgs[conv_rate][0];
		*val2 = tmp007_avgs[conv_rate][1];

		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}