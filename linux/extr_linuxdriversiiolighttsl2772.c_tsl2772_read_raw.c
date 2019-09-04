#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t als_gain; size_t prox_gain; int als_gain_trim; int /*<<< orphan*/  als_time; } ;
struct TYPE_3__ {int lux; int als_ch0; int als_ch1; } ;
struct tsl2772_chip {int prox_data; size_t id; TYPE_2__ settings; TYPE_1__ als_cur_info; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int const type; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 135 
#define  IIO_CHAN_INFO_CALIBSCALE 134 
#define  IIO_CHAN_INFO_INT_TIME 133 
#define  IIO_CHAN_INFO_PROCESSED 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_INTENSITY 130 
#define  IIO_LIGHT 129 
#define  IIO_PROXIMITY 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 int* tsl2772_als_gain ; 
 int /*<<< orphan*/  tsl2772_get_lux (struct iio_dev*) ; 
 int /*<<< orphan*/  tsl2772_get_prox (struct iio_dev*) ; 
 int** tsl2772_int_time_avail ; 
 int* tsl2772_prox_gain ; 

__attribute__((used)) static int tsl2772_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val,
			    int *val2,
			    long mask)
{
	struct tsl2772_chip *chip = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_LIGHT:
			tsl2772_get_lux(indio_dev);
			*val = chip->als_cur_info.lux;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_INTENSITY:
			tsl2772_get_lux(indio_dev);
			if (chan->channel == 0)
				*val = chip->als_cur_info.als_ch0;
			else
				*val = chip->als_cur_info.als_ch1;
			return IIO_VAL_INT;
		case IIO_PROXIMITY:
			tsl2772_get_prox(indio_dev);
			*val = chip->prox_data;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		if (chan->type == IIO_LIGHT)
			*val = tsl2772_als_gain[chip->settings.als_gain];
		else
			*val = tsl2772_prox_gain[chip->settings.prox_gain];
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBBIAS:
		*val = chip->settings.als_gain_trim;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = (256 - chip->settings.als_time) *
			tsl2772_int_time_avail[chip->id][3];
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}