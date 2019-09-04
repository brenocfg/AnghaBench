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
struct stk8312_data {scalar_t__ dready_trig; } ;
struct iio_dev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STK8312_MODE_STANDBY ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct stk8312_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (scalar_t__) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int stk8312_set_mode (struct stk8312_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stk8312_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct stk8312_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	if (data->dready_trig)
		iio_trigger_unregister(data->dready_trig);

	return stk8312_set_mode(data, STK8312_MODE_STANDBY);
}