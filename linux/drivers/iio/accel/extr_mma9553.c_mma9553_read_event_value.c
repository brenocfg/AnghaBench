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
struct TYPE_2__ {int /*<<< orphan*/  actthd; int /*<<< orphan*/  speed_step; } ;
struct mma9553_data {TYPE_1__ conf; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACTIVITY 131 
#define  IIO_EV_INFO_PERIOD 130 
#define  IIO_EV_INFO_VALUE 129 
#define  IIO_STEPS 128 
 int IIO_VAL_INT ; 
 int MMA9553_ACTIVITY_THD_TO_SEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_STEPCOALESCE ; 
 struct mma9553_data* iio_priv (struct iio_dev*) ; 
 int mma9553_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mma9553_read_event_value(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir,
				    enum iio_event_info info,
				    int *val, int *val2)
{
	struct mma9553_data *data = iio_priv(indio_dev);

	*val2 = 0;
	switch (info) {
	case IIO_EV_INFO_VALUE:
		switch (chan->type) {
		case IIO_STEPS:
			*val = mma9553_get_bits(data->conf.speed_step,
						MMA9553_MASK_CONF_STEPCOALESCE);
			return IIO_VAL_INT;
		case IIO_ACTIVITY:
			/*
			 * The device does not support confidence value levels.
			 * We set an average of 50%.
			 */
			*val = 50;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_EV_INFO_PERIOD:
		switch (chan->type) {
		case IIO_ACTIVITY:
			*val = MMA9553_ACTIVITY_THD_TO_SEC(data->conf.actthd);
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}