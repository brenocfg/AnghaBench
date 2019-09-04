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
struct cm36651_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 129 
#define  IIO_CHAN_INFO_RAW 128 
 int cm36651_read_channel (struct cm36651_data*,struct iio_chan_spec const*,int*) ; 
 int cm36651_read_int_time (struct cm36651_data*,struct iio_chan_spec const*,int*) ; 
 struct cm36651_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm36651_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct cm36651_data *cm36651 = iio_priv(indio_dev);
	int ret;

	mutex_lock(&cm36651->lock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = cm36651_read_channel(cm36651, chan, val);
		break;
	case IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		ret = cm36651_read_int_time(cm36651, chan, val2);
		break;
	default:
		ret = -EINVAL;
	}

	mutex_unlock(&cm36651->lock);

	return ret;
}