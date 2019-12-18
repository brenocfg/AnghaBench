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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int address; } ;
struct ak8974 {TYPE_1__* i2c; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 int ak8974_getresult (struct ak8974*,int /*<<< orphan*/ *) ; 
 int ak8974_trigmeas (struct ak8974*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ak8974* iio_priv (struct iio_dev*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ak8974_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2,
			   long mask)
{
	struct ak8974 *ak8974 = iio_priv(indio_dev);
	__le16 hw_values[3];
	int ret = -EINVAL;

	pm_runtime_get_sync(&ak8974->i2c->dev);
	mutex_lock(&ak8974->lock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (chan->address > 2) {
			dev_err(&ak8974->i2c->dev, "faulty channel address\n");
			ret = -EIO;
			goto out_unlock;
		}
		ret = ak8974_trigmeas(ak8974);
		if (ret)
			goto out_unlock;
		ret = ak8974_getresult(ak8974, hw_values);
		if (ret)
			goto out_unlock;

		/*
		 * We read all axes and discard all but one, for optimized
		 * reading, use the triggered buffer.
		 */
		*val = le16_to_cpu(hw_values[chan->address]);

		ret = IIO_VAL_INT;
	}

 out_unlock:
	mutex_unlock(&ak8974->lock);
	pm_runtime_mark_last_busy(&ak8974->i2c->dev);
	pm_runtime_put_autosuspend(&ak8974->i2c->dev);

	return ret;
}