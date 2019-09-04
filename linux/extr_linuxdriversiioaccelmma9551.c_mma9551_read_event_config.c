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
struct mma9551_data {int* event_enabled; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; int /*<<< orphan*/  channel2; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_INCLI 128 
 struct mma9551_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int mma9551_read_event_config(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir)
{
	struct mma9551_data *data = iio_priv(indio_dev);

	switch (chan->type) {
	case IIO_INCLI:
		/* IIO counts axes from 1, because IIO_NO_MOD is 0. */
		return data->event_enabled[chan->channel2 - 1];
	default:
		return -EINVAL;
	}
}