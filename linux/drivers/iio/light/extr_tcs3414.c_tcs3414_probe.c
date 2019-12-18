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
struct tcs3414_data {int gain; struct i2c_client* client; int /*<<< orphan*/  timing; int /*<<< orphan*/  control; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  TCS3414_CONTROL ; 
 int /*<<< orphan*/  TCS3414_CONTROL_POWER ; 
 int /*<<< orphan*/  TCS3414_DRV_NAME ; 
 int /*<<< orphan*/  TCS3414_GAIN ; 
 int /*<<< orphan*/  TCS3414_ID ; 
 int /*<<< orphan*/  TCS3414_INTEG_12MS ; 
 int /*<<< orphan*/  TCS3414_TIMING ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct tcs3414_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcs3414_buffer_setup_ops ; 
 int /*<<< orphan*/  tcs3414_channels ; 
 int /*<<< orphan*/  tcs3414_info ; 
 int /*<<< orphan*/  tcs3414_trigger_handler ; 

__attribute__((used)) static int tcs3414_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct tcs3414_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (indio_dev == NULL)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &tcs3414_info;
	indio_dev->name = TCS3414_DRV_NAME;
	indio_dev->channels = tcs3414_channels;
	indio_dev->num_channels = ARRAY_SIZE(tcs3414_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = i2c_smbus_read_byte_data(data->client, TCS3414_ID);
	if (ret < 0)
		return ret;

	switch (ret & 0xf0) {
	case 0x00:
		dev_info(&client->dev, "TCS3404 found\n");
		break;
	case 0x10:
		dev_info(&client->dev, "TCS3413/14/15/16 found\n");
		break;
	default:
		return -ENODEV;
	}

	data->control = TCS3414_CONTROL_POWER;
	ret = i2c_smbus_write_byte_data(data->client, TCS3414_CONTROL,
		data->control);
	if (ret < 0)
		return ret;

	data->timing = TCS3414_INTEG_12MS; /* free running */
	ret = i2c_smbus_write_byte_data(data->client, TCS3414_TIMING,
		data->timing);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_read_byte_data(data->client, TCS3414_GAIN);
	if (ret < 0)
		return ret;
	data->gain = ret;

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
		tcs3414_trigger_handler, &tcs3414_buffer_setup_ops);
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