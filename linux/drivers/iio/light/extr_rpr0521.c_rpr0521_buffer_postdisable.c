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
struct rpr0521_data {TYPE_1__* client; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RPR0521_MODE_ALS_MASK ; 
 int RPR0521_MODE_PXS_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct rpr0521_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpr0521_set_power_state (struct rpr0521_data*,int,int) ; 

__attribute__((used)) static int rpr0521_buffer_postdisable(struct iio_dev *indio_dev)
{
	int err;
	struct rpr0521_data *data = iio_priv(indio_dev);

	mutex_lock(&data->lock);
	err = rpr0521_set_power_state(data, false,
		(RPR0521_MODE_PXS_MASK | RPR0521_MODE_ALS_MASK));
	mutex_unlock(&data->lock);
	if (err)
		dev_err(&data->client->dev, "_buffer_postdisable fail\n");

	return err;
}