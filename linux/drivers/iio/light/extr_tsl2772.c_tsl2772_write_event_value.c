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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int als_thresh_high; int als_thresh_low; int prox_thres_high; int prox_thres_low; int als_persistence; int prox_persistence; int /*<<< orphan*/  prox_time; int /*<<< orphan*/  als_time; } ;
struct tsl2772_chip {size_t id; TYPE_1__ settings; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_DIR_FALLING 131 
#define  IIO_EV_DIR_RISING 130 
#define  IIO_EV_INFO_PERIOD 129 
#define  IIO_EV_INFO_VALUE 128 
 int /*<<< orphan*/  IIO_INTENSITY ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 int** tsl2772_int_time_avail ; 
 int tsl2772_invoke_change (struct iio_dev*) ; 

__attribute__((used)) static int tsl2772_write_event_value(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir,
				     enum iio_event_info info,
				     int val, int val2)
{
	struct tsl2772_chip *chip = iio_priv(indio_dev);
	int ret = -EINVAL, count, persistence;
	u8 time;

	switch (info) {
	case IIO_EV_INFO_VALUE:
		if (chan->type == IIO_INTENSITY) {
			switch (dir) {
			case IIO_EV_DIR_RISING:
				chip->settings.als_thresh_high = val;
				ret = 0;
				break;
			case IIO_EV_DIR_FALLING:
				chip->settings.als_thresh_low = val;
				ret = 0;
				break;
			default:
				break;
			}
		} else {
			switch (dir) {
			case IIO_EV_DIR_RISING:
				chip->settings.prox_thres_high = val;
				ret = 0;
				break;
			case IIO_EV_DIR_FALLING:
				chip->settings.prox_thres_low = val;
				ret = 0;
				break;
			default:
				break;
			}
		}
		break;
	case IIO_EV_INFO_PERIOD:
		if (chan->type == IIO_INTENSITY)
			time = chip->settings.als_time;
		else
			time = chip->settings.prox_time;

		count = 256 - time;
		persistence = ((val * 1000000) + val2) /
			(count * tsl2772_int_time_avail[chip->id][3]);

		if (chan->type == IIO_INTENSITY) {
			/* ALS filter values are 1, 2, 3, 5, 10, 15, ..., 60 */
			if (persistence > 3)
				persistence = (persistence / 5) + 3;

			chip->settings.als_persistence = persistence;
		} else {
			chip->settings.prox_persistence = persistence;
		}

		ret = 0;
		break;
	default:
		break;
	}

	if (ret < 0)
		return ret;

	return tsl2772_invoke_change(indio_dev);
}