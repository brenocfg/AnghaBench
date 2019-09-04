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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ams_iaqcore_data {int /*<<< orphan*/  lock; scalar_t__ last_update; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  ams_iaqcore_channels ; 
 int /*<<< orphan*/  ams_iaqcore_info ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct ams_iaqcore_data* iio_priv (struct iio_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ams_iaqcore_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct ams_iaqcore_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	/* so initial reading will complete */
	data->last_update = jiffies - HZ;
	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &ams_iaqcore_info;
	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_DIRECT_MODE;

	indio_dev->channels = ams_iaqcore_channels;
	indio_dev->num_channels = ARRAY_SIZE(ams_iaqcore_channels);

	return devm_iio_device_register(&client->dev, indio_dev);
}