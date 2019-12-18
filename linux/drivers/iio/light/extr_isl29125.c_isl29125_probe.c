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
struct isl29125_data {int conf1; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  ISL29125_CONF1 ; 
 int /*<<< orphan*/  ISL29125_DEVICE_ID ; 
 int /*<<< orphan*/  ISL29125_DRV_NAME ; 
 int ISL29125_ID ; 
 int ISL29125_MODE_PD ; 
 int ISL29125_MODE_RANGE ; 
 int /*<<< orphan*/  ISL29125_STATUS ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct isl29125_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isl29125_buffer_setup_ops ; 
 int /*<<< orphan*/  isl29125_channels ; 
 int /*<<< orphan*/  isl29125_info ; 
 int /*<<< orphan*/  isl29125_trigger_handler ; 

__attribute__((used)) static int isl29125_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct isl29125_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (indio_dev == NULL)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &isl29125_info;
	indio_dev->name = ISL29125_DRV_NAME;
	indio_dev->channels = isl29125_channels;
	indio_dev->num_channels = ARRAY_SIZE(isl29125_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = i2c_smbus_read_byte_data(data->client, ISL29125_DEVICE_ID);
	if (ret < 0)
		return ret;
	if (ret != ISL29125_ID)
		return -ENODEV;

	data->conf1 = ISL29125_MODE_PD | ISL29125_MODE_RANGE;
	ret = i2c_smbus_write_byte_data(data->client, ISL29125_CONF1,
		data->conf1);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(data->client, ISL29125_STATUS, 0);
	if (ret < 0)
		return ret;

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
		isl29125_trigger_handler, &isl29125_buffer_setup_ops);
	if (ret < 0)
		return ret;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto buffer_cleanup;

	return 0;

buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
	return ret;
}