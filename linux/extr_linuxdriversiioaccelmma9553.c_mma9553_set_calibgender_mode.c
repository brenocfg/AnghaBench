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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  filter; } ;
struct mma9553_data {int /*<<< orphan*/  mutex; TYPE_1__ conf; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_MALE ; 
 int /*<<< orphan*/  MMA9553_REG_CONF_FILTER ; 
 struct mma9553_data* iio_priv (struct iio_dev*) ; 
 int mma9553_set_config (struct mma9553_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma9553_set_calibgender_mode(struct iio_dev *indio_dev,
					const struct iio_chan_spec *chan,
					unsigned int mode)
{
	struct mma9553_data *data = iio_priv(indio_dev);
	u8 gender = !mode;
	int ret;

	if ((mode != 0) && (mode != 1))
		return -EINVAL;
	mutex_lock(&data->mutex);
	ret = mma9553_set_config(data, MMA9553_REG_CONF_FILTER,
				 &data->conf.filter, gender,
				 MMA9553_MASK_CONF_MALE);
	mutex_unlock(&data->mutex);

	return ret;
}