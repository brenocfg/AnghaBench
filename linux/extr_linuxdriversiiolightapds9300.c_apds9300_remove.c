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
struct i2c_client {int dummy; } ;
struct apds9300_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  apds9300_set_intr_state (struct apds9300_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apds9300_set_power_state (struct apds9300_data*,int /*<<< orphan*/ ) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct apds9300_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int apds9300_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct apds9300_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	/* Ensure that power off and interrupts are disabled */
	apds9300_set_intr_state(data, 0);
	apds9300_set_power_state(data, 0);

	return 0;
}