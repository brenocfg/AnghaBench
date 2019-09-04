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
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {size_t driver_data; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
struct ds1803_data {int /*<<< orphan*/ * cfg; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/ * ds1803_cfg ; 
 int /*<<< orphan*/  ds1803_channels ; 
 int /*<<< orphan*/  ds1803_info ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct ds1803_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ds1803_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct ds1803_data *data;
	struct iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	i2c_set_clientdata(client, indio_dev);

	data = iio_priv(indio_dev);
	data->client = client;
	data->cfg = &ds1803_cfg[id->driver_data];

	indio_dev->dev.parent = dev;
	indio_dev->info = &ds1803_info;
	indio_dev->channels = ds1803_channels;
	indio_dev->num_channels = ARRAY_SIZE(ds1803_channels);
	indio_dev->name = client->name;

	return devm_iio_device_register(dev, indio_dev);
}