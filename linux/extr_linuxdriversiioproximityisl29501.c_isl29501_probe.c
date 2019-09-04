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
struct isl29501_private {int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; int /*<<< orphan*/  modes; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ *,struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct isl29501_private* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  isl29501_channels ; 
 int /*<<< orphan*/  isl29501_info ; 
 int isl29501_init_chip (struct isl29501_private*) ; 
 int /*<<< orphan*/  isl29501_trigger_handler ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isl29501_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct isl29501_private *isl29501;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*isl29501));
	if (!indio_dev)
		return -ENOMEM;

	isl29501 = iio_priv(indio_dev);

	i2c_set_clientdata(client, indio_dev);
	isl29501->client = client;

	mutex_init(&isl29501->lock);

	ret = isl29501_init_chip(isl29501);
	if (ret < 0)
		return ret;

	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->dev.parent = &client->dev;
	indio_dev->channels = isl29501_channels;
	indio_dev->num_channels = ARRAY_SIZE(isl29501_channels);
	indio_dev->name = client->name;
	indio_dev->info = &isl29501_info;

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev,
					      iio_pollfunc_store_time,
					      isl29501_trigger_handler,
					      NULL);
	if (ret < 0) {
		dev_err(&client->dev, "unable to setup iio triggered buffer\n");
		return ret;
	}

	return devm_iio_device_register(&client->dev, indio_dev);
}