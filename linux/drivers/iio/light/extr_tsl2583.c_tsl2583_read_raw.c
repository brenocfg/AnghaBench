#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int als_gain_trim; size_t als_gain; int als_time; } ;
struct TYPE_4__ {int als_ch0; int als_ch1; } ;
struct tsl2583_chip {int /*<<< orphan*/  als_mutex; TYPE_2__ als_settings; TYPE_1__ als_cur_info; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  channel2; } ;
struct TYPE_6__ {int mean; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 132 
#define  IIO_CHAN_INFO_CALIBSCALE 131 
#define  IIO_CHAN_INFO_INT_TIME 130 
#define  IIO_CHAN_INFO_PROCESSED 129 
#define  IIO_CHAN_INFO_RAW 128 
 int /*<<< orphan*/  IIO_LIGHT ; 
 int /*<<< orphan*/  IIO_MOD_LIGHT_BOTH ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 TYPE_3__* gainadj ; 
 struct tsl2583_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tsl2583_get_lux (struct iio_dev*) ; 
 int tsl2583_set_pm_runtime_busy (struct tsl2583_chip*,int) ; 

__attribute__((used)) static int tsl2583_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct tsl2583_chip *chip = iio_priv(indio_dev);
	int ret, pm_ret;

	ret = tsl2583_set_pm_runtime_busy(chip, true);
	if (ret < 0)
		return ret;

	mutex_lock(&chip->als_mutex);

	ret = -EINVAL;
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (chan->type == IIO_LIGHT) {
			ret = tsl2583_get_lux(indio_dev);
			if (ret < 0)
				goto read_done;

			/*
			 * From page 20 of the TSL2581, TSL2583 data
			 * sheet (TAOS134 − MARCH 2011):
			 *
			 * One of the photodiodes (channel 0) is
			 * sensitive to both visible and infrared light,
			 * while the second photodiode (channel 1) is
			 * sensitive primarily to infrared light.
			 */
			if (chan->channel2 == IIO_MOD_LIGHT_BOTH)
				*val = chip->als_cur_info.als_ch0;
			else
				*val = chip->als_cur_info.als_ch1;

			ret = IIO_VAL_INT;
		}
		break;
	case IIO_CHAN_INFO_PROCESSED:
		if (chan->type == IIO_LIGHT) {
			ret = tsl2583_get_lux(indio_dev);
			if (ret < 0)
				goto read_done;

			*val = ret;
			ret = IIO_VAL_INT;
		}
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		if (chan->type == IIO_LIGHT) {
			*val = chip->als_settings.als_gain_trim;
			ret = IIO_VAL_INT;
		}
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		if (chan->type == IIO_LIGHT) {
			*val = gainadj[chip->als_settings.als_gain].mean;
			ret = IIO_VAL_INT;
		}
		break;
	case IIO_CHAN_INFO_INT_TIME:
		if (chan->type == IIO_LIGHT) {
			*val = 0;
			*val2 = chip->als_settings.als_time;
			ret = IIO_VAL_INT_PLUS_MICRO;
		}
		break;
	default:
		break;
	}

read_done:
	mutex_unlock(&chip->als_mutex);

	if (ret < 0)
		return ret;

	/*
	 * Preserve the ret variable if the call to
	 * tsl2583_set_pm_runtime_busy() is successful so the reading
	 * (if applicable) is returned to user space.
	 */
	pm_ret = tsl2583_set_pm_runtime_busy(chip, false);
	if (pm_ret < 0)
		return pm_ret;

	return ret;
}