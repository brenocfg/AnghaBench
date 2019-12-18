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
struct iio_chan_spec {scalar_t__ address; } ;
struct ads1015_data {scalar_t__ event_channel; int /*<<< orphan*/  lock; int /*<<< orphan*/  comp_mode; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int /*<<< orphan*/  ADS1015_CFG_COMP_MODE_WINDOW ; 
 int EINVAL ; 
#define  IIO_EV_DIR_EITHER 129 
#define  IIO_EV_DIR_RISING 128 
 struct ads1015_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads1015_read_event_config(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir)
{
	struct ads1015_data *data = iio_priv(indio_dev);
	int ret = 0;

	mutex_lock(&data->lock);
	if (data->event_channel == chan->address) {
		switch (dir) {
		case IIO_EV_DIR_RISING:
			ret = 1;
			break;
		case IIO_EV_DIR_EITHER:
			ret = (data->comp_mode == ADS1015_CFG_COMP_MODE_WINDOW);
			break;
		default:
			ret = -EINVAL;
			break;
		}
	}
	mutex_unlock(&data->lock);

	return ret;
}