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
typedef  int /*<<< orphan*/  u8 ;
struct pa12203001_data {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct pa12203001_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pa12203001_als_enable (struct pa12203001_data*,int /*<<< orphan*/ ) ; 
 int pa12203001_px_enable (struct pa12203001_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pa12203001_power_chip(struct iio_dev *indio_dev, u8 state)
{
	struct pa12203001_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->lock);
	ret = pa12203001_als_enable(data, state);
	if (ret < 0)
		goto out;

	ret = pa12203001_px_enable(data, state);

out:
	mutex_unlock(&data->lock);
	return ret;
}