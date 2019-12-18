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
struct max5432_data {unsigned long ohm; struct i2c_client* client; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct max5432_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  max5432_channels ; 
 int /*<<< orphan*/  max5432_info ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 

__attribute__((used)) static int max5432_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct iio_dev *indio_dev;
	struct max5432_data *data;

	indio_dev = devm_iio_device_alloc(dev, sizeof(struct max5432_data));
	if (!indio_dev)
		return -ENOMEM;

	i2c_set_clientdata(client, indio_dev);

	data = iio_priv(indio_dev);
	data->client = client;
	data->ohm = (unsigned long)of_device_get_match_data(dev);

	indio_dev->dev.parent = dev;
	indio_dev->info = &max5432_info;
	indio_dev->channels = max5432_channels;
	indio_dev->num_channels = ARRAY_SIZE(max5432_channels);
	indio_dev->name = client->name;

	return devm_iio_device_register(dev, indio_dev);
}