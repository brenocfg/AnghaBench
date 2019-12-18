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
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct cm36651_data {int /*<<< orphan*/  ara_client; int /*<<< orphan*/  ps_client; int /*<<< orphan*/  vled_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct cm36651_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cm36651_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct cm36651_data *cm36651 = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	regulator_disable(cm36651->vled_reg);
	free_irq(client->irq, indio_dev);
	i2c_unregister_device(cm36651->ps_client);
	i2c_unregister_device(cm36651->ara_client);

	return 0;
}