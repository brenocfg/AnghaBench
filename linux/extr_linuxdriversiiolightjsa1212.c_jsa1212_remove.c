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
struct jsa1212_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct jsa1212_data* iio_priv (struct iio_dev*) ; 
 int jsa1212_power_off (struct jsa1212_data*) ; 

__attribute__((used)) static int jsa1212_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct jsa1212_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	return jsa1212_power_off(data);
}