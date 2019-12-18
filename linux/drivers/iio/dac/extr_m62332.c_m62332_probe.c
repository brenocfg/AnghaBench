#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct m62332_data {int /*<<< orphan*/  vcc; int /*<<< orphan*/  mutex; struct i2c_client* client; } ;
struct TYPE_4__ {TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  channels; int /*<<< orphan*/  num_channels; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  platform_data; } ;
struct i2c_client {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int iio_map_array_register (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_map_array_unregister (struct iio_dev*) ; 
 struct m62332_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  m62332_channels ; 
 int /*<<< orphan*/  m62332_info ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int m62332_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct m62332_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	mutex_init(&data->mutex);

	data->vcc = devm_regulator_get(&client->dev, "VCC");
	if (IS_ERR(data->vcc))
		return PTR_ERR(data->vcc);

	/* establish that the iio_dev is a child of the i2c device */
	indio_dev->dev.parent = &client->dev;

	indio_dev->num_channels = ARRAY_SIZE(m62332_channels);
	indio_dev->channels = m62332_channels;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &m62332_info;

	ret = iio_map_array_register(indio_dev, client->dev.platform_data);
	if (ret < 0)
		return ret;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto err;

	return 0;

err:
	iio_map_array_unregister(indio_dev);

	return ret;
}