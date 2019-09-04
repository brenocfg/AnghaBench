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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; } ;
struct gp2ap020a00f_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_FALLING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_RISING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_PROX_FALLING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_PROX_RISING_EV ; 
 int IIO_EV_DIR_RISING ; 
#define  IIO_LIGHT 129 
#define  IIO_PROXIMITY 128 
 struct gp2ap020a00f_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gp2ap020a00f_read_event_config(struct iio_dev *indio_dev,
					   const struct iio_chan_spec *chan,
					   enum iio_event_type type,
					   enum iio_event_direction dir)
{
	struct gp2ap020a00f_data *data = iio_priv(indio_dev);
	int event_en = 0;

	mutex_lock(&data->lock);

	switch (chan->type) {
	case IIO_PROXIMITY:
		if (dir == IIO_EV_DIR_RISING)
			event_en = test_bit(GP2AP020A00F_FLAG_PROX_RISING_EV,
								&data->flags);
		else
			event_en = test_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV,
								&data->flags);
		break;
	case IIO_LIGHT:
		if (dir == IIO_EV_DIR_RISING)
			event_en = test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV,
								&data->flags);
		else
			event_en = test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV,
								&data->flags);
		break;
	default:
		event_en = -EINVAL;
		break;
	}

	mutex_unlock(&data->lock);

	return event_en;
}