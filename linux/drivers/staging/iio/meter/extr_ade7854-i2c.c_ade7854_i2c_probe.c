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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct ade7854_state {int /*<<< orphan*/  irq; struct i2c_client* i2c; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ade7854_i2c_read_reg ; 
 int /*<<< orphan*/  ade7854_i2c_write_reg ; 
 int ade7854_probe (struct iio_dev*,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct ade7854_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ade7854_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct ade7854_state *st;
	struct iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;
	st = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	st->read_reg = ade7854_i2c_read_reg;
	st->write_reg = ade7854_i2c_write_reg;
	st->i2c = client;
	st->irq = client->irq;

	return ade7854_probe(indio_dev, &client->dev);
}