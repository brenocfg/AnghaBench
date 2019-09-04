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
struct nau7802_state {int /*<<< orphan*/  data_lock; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct iio_dev*) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct nau7802_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nau7802_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct nau7802_state *st = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	mutex_destroy(&st->lock);
	mutex_destroy(&st->data_lock);
	if (client->irq)
		free_irq(client->irq, indio_dev);

	return 0;
}