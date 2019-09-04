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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct gp2ap020a00f_data {int /*<<< orphan*/  vled_reg; int /*<<< orphan*/  trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_SHUTDOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 int gp2ap020a00f_set_operation_mode (struct gp2ap020a00f_data*,int /*<<< orphan*/ ) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct gp2ap020a00f_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp2ap020a00f_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct gp2ap020a00f_data *data = iio_priv(indio_dev);
	int err;

	err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_SHUTDOWN);
	if (err < 0)
		dev_err(&indio_dev->dev, "Failed to power off the device.\n");

	iio_device_unregister(indio_dev);
	iio_trigger_unregister(data->trig);
	free_irq(client->irq, indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	regulator_disable(data->vled_reg);

	return 0;
}