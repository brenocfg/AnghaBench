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
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 int** tsl2772_int_time_avail ; 

__attribute__((used)) static int tsl2772_read_event_value(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir,
				    enum iio_event_info info,
				    int *val, int *val2)
{
	struct tsl2772_chip *chip = iio_priv(indio_dev);
	int filter_delay, persistence;
	u8 time;

	switch (info) {
	case IIO_EV_INFO_VALUE:
		if (chan->type == IIO_INTENSITY) {
			switch (dir) {
			case IIO_EV_DIR_RISING:
				*val = chip->settings.als_thresh_high;
				return IIO_VAL_INT;
			case IIO_EV_DIR_FALLING:
				*val = chip->settings.als_thresh_low;
				return IIO_VAL_INT;
			default:
				return -EINVAL;
			}
		} else {
			switch (dir) {
			case IIO_EV_DIR_RISING:
				*val = chip->settings.prox_thres_high;
				return IIO_VAL_INT;
			case IIO_EV_DIR_FALLING:
				*val = chip->settings.prox_thres_low;
				return IIO_VAL_INT;
			default:
				return -EINVAL;
			}
		}
		break;
	case IIO_EV_INFO_PERIOD:
		if (chan->type == IIO_INTENSITY) {
			time = chip->settings.als_time;
			persistence = chip->settings.als_persistence;

			/* ALS filter values are 1, 2, 3, 5, 10, 15, ..., 60 */
			if (persistence > 3)
				persistence = (persistence - 3) * 5;
		} else {
			time = chip->settings.prox_time;
			persistence = chip->settings.prox_persistence;
		}

		filter_delay = persistence * (256 - time) *
			tsl2772_int_time_avail[chip->id][3];

		*val = filter_delay / 1000000;
		*val2 = filter_delay % 1000000;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}