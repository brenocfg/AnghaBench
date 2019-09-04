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

/* Variables and functions */
 int /*<<< orphan*/  CM3232_CMD_ALS_DISABLE ; 
 int /*<<< orphan*/  CM3232_REG_ADDR_CMD ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 

__attribute__((used)) static int cm3232_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);

	i2c_smbus_write_byte_data(client, CM3232_REG_ADDR_CMD,
		CM3232_CMD_ALS_DISABLE);

	iio_device_unregister(indio_dev);

	return 0;
}