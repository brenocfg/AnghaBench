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
struct mb1232_data {int irqnr; int /*<<< orphan*/  ranging; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int /*<<< orphan*/  adapter; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int I2C_FUNC_SMBUS_READ_BYTE ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (struct device*,struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct mb1232_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb1232_channels ; 
 int /*<<< orphan*/  mb1232_handle_irq ; 
 int /*<<< orphan*/  mb1232_info ; 
 int /*<<< orphan*/  mb1232_trigger_handler ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mb1232_probe(struct i2c_client *client,
					 const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct mb1232_data *data;
	int ret;
	struct device *dev = &client->dev;

	if (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_READ_BYTE |
					I2C_FUNC_SMBUS_WRITE_BYTE))
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->info = &mb1232_info;
	indio_dev->name = id->name;
	indio_dev->dev.parent = dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = mb1232_channels;
	indio_dev->num_channels = ARRAY_SIZE(mb1232_channels);

	mutex_init(&data->lock);

	init_completion(&data->ranging);

	data->irqnr = irq_of_parse_and_map(dev->of_node, 0);
	if (data->irqnr <= 0) {
		/* usage of interrupt is optional */
		data->irqnr = -1;
	} else {
		ret = devm_request_irq(dev, data->irqnr, mb1232_handle_irq,
				IRQF_TRIGGER_FALLING, id->name, indio_dev);
		if (ret < 0) {
			dev_err(dev, "request_irq: %d\n", ret);
			return ret;
		}
	}

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
			iio_pollfunc_store_time, mb1232_trigger_handler, NULL);
	if (ret < 0) {
		dev_err(dev, "setup of iio triggered buffer failed\n");
		return ret;
	}

	return devm_iio_device_register(dev, indio_dev);
}