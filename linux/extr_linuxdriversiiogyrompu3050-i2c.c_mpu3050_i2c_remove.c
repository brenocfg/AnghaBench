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
struct mpu3050 {scalar_t__ i2cmux; } ;
struct iio_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct iio_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (scalar_t__) ; 
 struct mpu3050* iio_priv (struct iio_dev*) ; 
 int mpu3050_common_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpu3050_i2c_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = dev_get_drvdata(&client->dev);
	struct mpu3050 *mpu3050 = iio_priv(indio_dev);

	if (mpu3050->i2cmux)
		i2c_mux_del_adapters(mpu3050->i2cmux);

	return mpu3050_common_remove(&client->dev);
}