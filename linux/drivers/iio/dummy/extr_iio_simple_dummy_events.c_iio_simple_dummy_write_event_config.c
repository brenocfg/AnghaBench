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
struct iio_dummy_state {int event_en; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACTIVITY 132 
 int IIO_EV_DIR_RISING ; 
#define  IIO_EV_TYPE_CHANGE 131 
#define  IIO_EV_TYPE_THRESH 130 
#define  IIO_STEPS 129 
#define  IIO_VOLTAGE 128 
 struct iio_dummy_state* iio_priv (struct iio_dev*) ; 

int iio_simple_dummy_write_event_config(struct iio_dev *indio_dev,
					const struct iio_chan_spec *chan,
					enum iio_event_type type,
					enum iio_event_direction dir,
					int state)
{
	struct iio_dummy_state *st = iio_priv(indio_dev);

	/*
	 *  Deliberately over the top code splitting to illustrate
	 * how this is done when multiple events exist.
	 */
	switch (chan->type) {
	case IIO_VOLTAGE:
		switch (type) {
		case IIO_EV_TYPE_THRESH:
			if (dir == IIO_EV_DIR_RISING)
				st->event_en = state;
			else
				return -EINVAL;
			break;
		default:
			return -EINVAL;
		}
		break;
	case IIO_ACTIVITY:
		switch (type) {
		case IIO_EV_TYPE_THRESH:
			st->event_en = state;
			break;
		default:
			return -EINVAL;
		}
		break;
	case IIO_STEPS:
		switch (type) {
		case IIO_EV_TYPE_CHANGE:
			st->event_en = state;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}