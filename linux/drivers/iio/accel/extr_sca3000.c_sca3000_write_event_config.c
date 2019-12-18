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
struct sca3000_state {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel2; int /*<<< orphan*/  address; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_MOD_X 131 
#define  IIO_MOD_X_AND_Y_AND_Z 130 
#define  IIO_MOD_Y 129 
#define  IIO_MOD_Z 128 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_freefall_set_state (struct iio_dev*,int) ; 
 int sca3000_motion_detect_set_state (struct iio_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sca3000_write_event_config(struct iio_dev *indio_dev,
				      const struct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_direction dir,
				      int state)
{
	struct sca3000_state *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&st->lock);
	switch (chan->channel2) {
	case IIO_MOD_X_AND_Y_AND_Z:
		ret = sca3000_freefall_set_state(indio_dev, state);
		break;

	case IIO_MOD_X:
	case IIO_MOD_Y:
	case IIO_MOD_Z:
		ret = sca3000_motion_detect_set_state(indio_dev,
						      chan->address,
						      state);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	mutex_unlock(&st->lock);

	return ret;
}