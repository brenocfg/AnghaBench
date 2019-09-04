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
struct mag3110_data {int ctrl_reg1; int sleep_val; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int scan_index; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int MAG3110_CTRL_AC ; 
 int MAG3110_CTRL_DR_MASK ; 
 int MAG3110_CTRL_DR_SHIFT ; 
 int /*<<< orphan*/  MAG3110_CTRL_REG1 ; 
 int /*<<< orphan*/  MAG3110_OFF_X ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct mag3110_data* iio_priv (struct iio_dev*) ; 
 int mag3110_calculate_sleep (struct mag3110_data*) ; 
 int mag3110_change_config (struct mag3110_data*,int /*<<< orphan*/ ,int) ; 
 int mag3110_get_samp_freq_index (struct mag3110_data*,int,int) ; 

__attribute__((used)) static int mag3110_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct mag3110_data *data = iio_priv(indio_dev);
	int rate, ret;

	ret = iio_device_claim_direct_mode(indio_dev);
	if (ret)
		return ret;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		rate = mag3110_get_samp_freq_index(data, val, val2);
		if (rate < 0) {
			ret = -EINVAL;
			break;
		}
		data->ctrl_reg1 &= 0xff & ~MAG3110_CTRL_DR_MASK
					& ~MAG3110_CTRL_AC;
		data->ctrl_reg1 |= rate << MAG3110_CTRL_DR_SHIFT;
		data->sleep_val = mag3110_calculate_sleep(data);
		if (data->sleep_val < 40)
			data->ctrl_reg1 |= MAG3110_CTRL_AC;

		ret = mag3110_change_config(data, MAG3110_CTRL_REG1,
					    data->ctrl_reg1);
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		if (val < -10000 || val > 10000) {
			ret = -EINVAL;
			break;
		}
		ret = i2c_smbus_write_word_swapped(data->client,
			MAG3110_OFF_X + 2 * chan->scan_index, val << 1);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	iio_device_release_direct_mode(indio_dev);
	return ret;
}