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
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct apds9300_data {int /*<<< orphan*/  mutex; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS9300_DRV_NAME ; 
 int /*<<< orphan*/  APDS9300_IRQ_NAME ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  apds9300_channels ; 
 int apds9300_chip_init (struct apds9300_data*) ; 
 int /*<<< orphan*/  apds9300_info ; 
 int /*<<< orphan*/  apds9300_info_no_irq ; 
 int /*<<< orphan*/  apds9300_interrupt_handler ; 
 int /*<<< orphan*/  apds9300_set_power_state (struct apds9300_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct apds9300_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apds9300_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct apds9300_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	ret = apds9300_chip_init(data);
	if (ret < 0)
		goto err;

	mutex_init(&data->mutex);

	indio_dev->dev.parent = &client->dev;
	indio_dev->channels = apds9300_channels;
	indio_dev->num_channels = ARRAY_SIZE(apds9300_channels);
	indio_dev->name = APDS9300_DRV_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (client->irq)
		indio_dev->info = &apds9300_info;
	else
		indio_dev->info = &apds9300_info_no_irq;

	if (client->irq) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
				NULL, apds9300_interrupt_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				APDS9300_IRQ_NAME, indio_dev);
		if (ret) {
			dev_err(&client->dev, "irq request error %d\n", -ret);
			goto err;
		}
	}

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto err;

	return 0;

err:
	/* Ensure that power off in case of error */
	apds9300_set_power_state(data, 0);
	return ret;
}