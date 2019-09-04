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
struct iio_chan_spec {int dummy; } ;
struct bmc150_accel_data {int ev_enable_state; int /*<<< orphan*/  mutex; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_ACCEL_INT_ANY_MOTION ; 
 int bmc150_accel_set_interrupt (struct bmc150_accel_data*,int /*<<< orphan*/ ,int) ; 
 struct bmc150_accel_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmc150_accel_write_event_config(struct iio_dev *indio_dev,
					   const struct iio_chan_spec *chan,
					   enum iio_event_type type,
					   enum iio_event_direction dir,
					   int state)
{
	struct bmc150_accel_data *data = iio_priv(indio_dev);
	int ret;

	if (state == data->ev_enable_state)
		return 0;

	mutex_lock(&data->mutex);

	ret = bmc150_accel_set_interrupt(data, BMC150_ACCEL_INT_ANY_MOTION,
					 state);
	if (ret < 0) {
		mutex_unlock(&data->mutex);
		return ret;
	}

	data->ev_enable_state = state;
	mutex_unlock(&data->mutex);

	return 0;
}