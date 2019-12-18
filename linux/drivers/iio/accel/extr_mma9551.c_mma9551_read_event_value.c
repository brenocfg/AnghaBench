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
typedef  int u8 ;
struct mma9551_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_INCLI 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MMA9551_APPID_TILT ; 
 int MMA9551_TILT_ANG_THRESH_MASK ; 
 int /*<<< orphan*/  MMA9551_TILT_CFG_REG ; 
 struct mma9551_data* iio_priv (struct iio_dev*) ; 
 int mma9551_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma9551_read_event_value(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir,
				    enum iio_event_info info,
				    int *val, int *val2)
{
	struct mma9551_data *data = iio_priv(indio_dev);
	int ret;
	u8 tmp;

	switch (chan->type) {
	case IIO_INCLI:
		mutex_lock(&data->mutex);
		ret = mma9551_read_config_byte(data->client,
					       MMA9551_APPID_TILT,
					       MMA9551_TILT_CFG_REG, &tmp);
		mutex_unlock(&data->mutex);
		if (ret < 0)
			return ret;
		*val = tmp & MMA9551_TILT_ANG_THRESH_MASK;
		*val2 = 0;
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}