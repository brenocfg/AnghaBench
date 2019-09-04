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
struct ak8974 {TYPE_1__* i2c; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ak8974_getresult (struct ak8974*,int /*<<< orphan*/ *) ; 
 int ak8974_trigmeas (struct ak8974*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct ak8974* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ak8974_fill_buffer(struct iio_dev *indio_dev)
{
	struct ak8974 *ak8974 = iio_priv(indio_dev);
	int ret;
	__le16 hw_values[8]; /* Three axes + 64bit padding */

	pm_runtime_get_sync(&ak8974->i2c->dev);
	mutex_lock(&ak8974->lock);

	ret = ak8974_trigmeas(ak8974);
	if (ret) {
		dev_err(&ak8974->i2c->dev, "error triggering measure\n");
		goto out_unlock;
	}
	ret = ak8974_getresult(ak8974, hw_values);
	if (ret) {
		dev_err(&ak8974->i2c->dev, "error getting measures\n");
		goto out_unlock;
	}

	iio_push_to_buffers_with_timestamp(indio_dev, hw_values,
					   iio_get_time_ns(indio_dev));

 out_unlock:
	mutex_unlock(&ak8974->lock);
	pm_runtime_mark_last_busy(&ak8974->i2c->dev);
	pm_runtime_put_autosuspend(&ak8974->i2c->dev);
}