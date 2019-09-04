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
struct mag3110_data {int ctrl_reg1; int sleep_val; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int MAG3110_CTRL_AC ; 
 int /*<<< orphan*/  MAG3110_CTRL_AUTO_MRST_EN ; 
 int MAG3110_CTRL_DR_DEFAULT ; 
 int MAG3110_CTRL_DR_SHIFT ; 
 int /*<<< orphan*/  MAG3110_CTRL_REG1 ; 
 int /*<<< orphan*/  MAG3110_CTRL_REG2 ; 
 int MAG3110_DEVICE_ID ; 
 int /*<<< orphan*/  MAG3110_WHO_AM_I ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct mag3110_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mag3110_calculate_sleep (struct mag3110_data*) ; 
 int mag3110_change_config (struct mag3110_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mag3110_channels ; 
 int /*<<< orphan*/  mag3110_info ; 
 int /*<<< orphan*/  mag3110_scan_masks ; 
 int /*<<< orphan*/  mag3110_standby (struct mag3110_data*) ; 
 int /*<<< orphan*/  mag3110_trigger_handler ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mag3110_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct mag3110_data *data;
	struct iio_dev *indio_dev;
	int ret;

	ret = i2c_smbus_read_byte_data(client, MAG3110_WHO_AM_I);
	if (ret < 0)
		return ret;
	if (ret != MAG3110_DEVICE_ID)
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	i2c_set_clientdata(client, indio_dev);
	indio_dev->info = &mag3110_info;
	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = mag3110_channels;
	indio_dev->num_channels = ARRAY_SIZE(mag3110_channels);
	indio_dev->available_scan_masks = mag3110_scan_masks;

	data->ctrl_reg1 = MAG3110_CTRL_DR_DEFAULT << MAG3110_CTRL_DR_SHIFT;
	data->sleep_val = mag3110_calculate_sleep(data);
	if (data->sleep_val < 40)
		data->ctrl_reg1 |= MAG3110_CTRL_AC;

	ret = mag3110_change_config(data, MAG3110_CTRL_REG1, data->ctrl_reg1);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(client, MAG3110_CTRL_REG2,
		MAG3110_CTRL_AUTO_MRST_EN);
	if (ret < 0)
		goto standby_on_error;

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
		mag3110_trigger_handler, NULL);
	if (ret < 0)
		goto standby_on_error;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto buffer_cleanup;
	return 0;

buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
standby_on_error:
	mag3110_standby(iio_priv(indio_dev));
	return ret;
}