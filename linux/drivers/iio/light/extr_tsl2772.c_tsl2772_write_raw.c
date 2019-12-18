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
struct TYPE_2__ {int als_gain; int prox_gain; int als_gain_trim; int als_time; } ;
struct tsl2772_chip {size_t id; TYPE_1__ settings; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_INT_TIME 128 
 int /*<<< orphan*/  IIO_INTENSITY ; 
 int TSL2772_ALS_GAIN_TRIM_MAX ; 
 int TSL2772_ALS_GAIN_TRIM_MIN ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 int** tsl2772_int_time_avail ; 
 int tsl2772_invoke_change (struct iio_dev*) ; 

__attribute__((used)) static int tsl2772_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val,
			     int val2,
			     long mask)
{
	struct tsl2772_chip *chip = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_CALIBSCALE:
		if (chan->type == IIO_INTENSITY) {
			switch (val) {
			case 1:
				chip->settings.als_gain = 0;
				break;
			case 8:
				chip->settings.als_gain = 1;
				break;
			case 16:
				chip->settings.als_gain = 2;
				break;
			case 120:
				chip->settings.als_gain = 3;
				break;
			default:
				return -EINVAL;
			}
		} else {
			switch (val) {
			case 1:
				chip->settings.prox_gain = 0;
				break;
			case 2:
				chip->settings.prox_gain = 1;
				break;
			case 4:
				chip->settings.prox_gain = 2;
				break;
			case 8:
				chip->settings.prox_gain = 3;
				break;
			default:
				return -EINVAL;
			}
		}
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		if (val < TSL2772_ALS_GAIN_TRIM_MIN ||
		    val > TSL2772_ALS_GAIN_TRIM_MAX)
			return -EINVAL;

		chip->settings.als_gain_trim = val;
		break;
	case IIO_CHAN_INFO_INT_TIME:
		if (val != 0 || val2 < tsl2772_int_time_avail[chip->id][1] ||
		    val2 > tsl2772_int_time_avail[chip->id][5])
			return -EINVAL;

		chip->settings.als_time = 256 -
			(val2 / tsl2772_int_time_avail[chip->id][3]);
		break;
	default:
		return -EINVAL;
	}

	return tsl2772_invoke_change(indio_dev);
}