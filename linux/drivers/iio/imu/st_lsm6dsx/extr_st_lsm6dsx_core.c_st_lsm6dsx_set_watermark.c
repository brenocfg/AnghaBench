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
struct st_lsm6dsx_sensor {unsigned int watermark; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {int /*<<< orphan*/  conf_lock; TYPE_1__* settings; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {unsigned int max_fifo_size; } ;

/* Variables and functions */
 int EINVAL ; 
 struct st_lsm6dsx_sensor* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int st_lsm6dsx_update_watermark (struct st_lsm6dsx_sensor*,unsigned int) ; 

int st_lsm6dsx_set_watermark(struct iio_dev *iio_dev, unsigned int val)
{
	struct st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	struct st_lsm6dsx_hw *hw = sensor->hw;
	int err;

	if (val < 1 || val > hw->settings->max_fifo_size)
		return -EINVAL;

	mutex_lock(&hw->conf_lock);

	err = st_lsm6dsx_update_watermark(sensor, val);

	mutex_unlock(&hw->conf_lock);

	if (err < 0)
		return err;

	sensor->watermark = val;

	return 0;
}