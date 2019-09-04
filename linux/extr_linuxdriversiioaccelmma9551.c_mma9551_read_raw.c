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
struct mma9551_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACCEL 132 
#define  IIO_CHAN_INFO_PROCESSED 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_INCLI 128 
 struct mma9551_data* iio_priv (struct iio_dev*) ; 
 int mma9551_read_accel_chan (int /*<<< orphan*/ ,struct iio_chan_spec const*,int*,int*) ; 
 int mma9551_read_accel_scale (int*,int*) ; 
 int mma9551_read_incli_chan (int /*<<< orphan*/ ,struct iio_chan_spec const*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma9551_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct mma9551_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_INCLI:
			mutex_lock(&data->mutex);
			ret = mma9551_read_incli_chan(data->client, chan, val);
			mutex_unlock(&data->mutex);
			return ret;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_ACCEL:
			mutex_lock(&data->mutex);
			ret = mma9551_read_accel_chan(data->client,
						      chan, val, val2);
			mutex_unlock(&data->mutex);
			return ret;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ACCEL:
			return mma9551_read_accel_scale(val, val2);
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}