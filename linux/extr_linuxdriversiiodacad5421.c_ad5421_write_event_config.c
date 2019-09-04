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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int type; } ;
struct ad5421_state {unsigned int fault_mask; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 unsigned int AD5421_FAULT_OVER_CURRENT ; 
 unsigned int AD5421_FAULT_TEMP_OVER_140 ; 
 unsigned int AD5421_FAULT_UNDER_CURRENT ; 
 int EINVAL ; 
#define  IIO_CURRENT 129 
 int IIO_EV_DIR_RISING ; 
#define  IIO_TEMP 128 
 struct ad5421_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5421_write_event_config(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, int state)
{
	struct ad5421_state *st = iio_priv(indio_dev);
	unsigned int mask;

	switch (chan->type) {
	case IIO_CURRENT:
		if (dir == IIO_EV_DIR_RISING)
			mask = AD5421_FAULT_OVER_CURRENT;
		else
			mask = AD5421_FAULT_UNDER_CURRENT;
		break;
	case IIO_TEMP:
		mask = AD5421_FAULT_TEMP_OVER_140;
		break;
	default:
		return -EINVAL;
	}

	mutex_lock(&indio_dev->mlock);
	if (state)
		st->fault_mask |= mask;
	else
		st->fault_mask &= ~mask;
	mutex_unlock(&indio_dev->mlock);

	return 0;
}