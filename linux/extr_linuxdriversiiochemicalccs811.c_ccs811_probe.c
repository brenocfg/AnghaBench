#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {TYPE_3__* trig; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct ccs811_data {TYPE_3__* drdy_trig; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ops; TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCS811_HW_ID ; 
 int CCS811_HW_ID_VALUE ; 
 int /*<<< orphan*/  CCS811_HW_VERSION ; 
 int CCS811_HW_VERSION_MASK ; 
 int CCS811_HW_VERSION_VALUE ; 
 int /*<<< orphan*/  CCS811_MEAS_MODE ; 
 int /*<<< orphan*/  CCS811_MODE_IDLE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  ccs811_channels ; 
 int /*<<< orphan*/  ccs811_data_rdy_trigger_poll ; 
 int /*<<< orphan*/  ccs811_info ; 
 int ccs811_setup (struct i2c_client*) ; 
 int /*<<< orphan*/  ccs811_trigger_handler ; 
 int /*<<< orphan*/  ccs811_trigger_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ccs811_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_get (TYPE_3__*) ; 
 int iio_trigger_register (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_3__*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccs811_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct ccs811_data *data;
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WRITE_BYTE
				     | I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		return -EOPNOTSUPP;

	/* Check hardware id (should be 0x81 for this family of devices) */
	ret = i2c_smbus_read_byte_data(client, CCS811_HW_ID);
	if (ret < 0)
		return ret;

	if (ret != CCS811_HW_ID_VALUE) {
		dev_err(&client->dev, "hardware id doesn't match CCS81x\n");
		return -ENODEV;
	}

	ret = i2c_smbus_read_byte_data(client, CCS811_HW_VERSION);
	if (ret < 0)
		return ret;

	if ((ret & CCS811_HW_VERSION_MASK) != CCS811_HW_VERSION_VALUE) {
		dev_err(&client->dev, "no CCS811 sensor\n");
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	ret = ccs811_setup(client);
	if (ret < 0)
		return ret;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->name = id->name;
	indio_dev->info = &ccs811_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	indio_dev->channels = ccs811_channels;
	indio_dev->num_channels = ARRAY_SIZE(ccs811_channels);

	if (client->irq > 0) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
						ccs811_data_rdy_trigger_poll,
						NULL,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"ccs811_irq", indio_dev);
		if (ret) {
			dev_err(&client->dev, "irq request error %d\n", -ret);
			goto err_poweroff;
		}

		data->drdy_trig = devm_iio_trigger_alloc(&client->dev,
							 "%s-dev%d",
							 indio_dev->name,
							 indio_dev->id);
		if (!data->drdy_trig) {
			ret = -ENOMEM;
			goto err_poweroff;
		}

		data->drdy_trig->dev.parent = &client->dev;
		data->drdy_trig->ops = &ccs811_trigger_ops;
		iio_trigger_set_drvdata(data->drdy_trig, indio_dev);
		indio_dev->trig = data->drdy_trig;
		iio_trigger_get(indio_dev->trig);
		ret = iio_trigger_register(data->drdy_trig);
		if (ret)
			goto err_poweroff;
	}

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 ccs811_trigger_handler, NULL);

	if (ret < 0) {
		dev_err(&client->dev, "triggered buffer setup failed\n");
		goto err_trigger_unregister;
	}

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(&client->dev, "unable to register iio device\n");
		goto err_buffer_cleanup;
	}
	return 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_trigger_unregister:
	if (data->drdy_trig)
		iio_trigger_unregister(data->drdy_trig);
err_poweroff:
	i2c_smbus_write_byte_data(client, CCS811_MEAS_MODE, CCS811_MODE_IDLE);

	return ret;
}