#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sx9500_data {int trigger_enabled; TYPE_3__* trig; int /*<<< orphan*/  regmap; int /*<<< orphan*/  completion; int /*<<< orphan*/  mutex; struct i2c_client* client; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ops; TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SX9500_DRIVER_NAME ; 
 int /*<<< orphan*/  SX9500_IRQ_NAME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct sx9500_data* iio_priv (struct iio_dev*) ; 
 int iio_trigger_register (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_3__*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx9500_buffer_setup_ops ; 
 int /*<<< orphan*/  sx9500_channels ; 
 int /*<<< orphan*/  sx9500_gpio_probe (struct i2c_client*,struct sx9500_data*) ; 
 int /*<<< orphan*/  sx9500_info ; 
 int sx9500_init_device (struct iio_dev*) ; 
 int /*<<< orphan*/  sx9500_irq_handler ; 
 int /*<<< orphan*/  sx9500_irq_thread_handler ; 
 int /*<<< orphan*/  sx9500_regmap_config ; 
 int /*<<< orphan*/  sx9500_trigger_handler ; 
 int /*<<< orphan*/  sx9500_trigger_ops ; 

__attribute__((used)) static int sx9500_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret;
	struct iio_dev *indio_dev;
	struct sx9500_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (indio_dev == NULL)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->mutex);
	init_completion(&data->completion);
	data->trigger_enabled = false;

	data->regmap = devm_regmap_init_i2c(client, &sx9500_regmap_config);
	if (IS_ERR(data->regmap))
		return PTR_ERR(data->regmap);

	indio_dev->dev.parent = &client->dev;
	indio_dev->name = SX9500_DRIVER_NAME;
	indio_dev->channels = sx9500_channels;
	indio_dev->num_channels = ARRAY_SIZE(sx9500_channels);
	indio_dev->info = &sx9500_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	i2c_set_clientdata(client, indio_dev);

	sx9500_gpio_probe(client, data);

	ret = sx9500_init_device(indio_dev);
	if (ret < 0)
		return ret;

	if (client->irq <= 0)
		dev_warn(&client->dev, "no valid irq found\n");
	else {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
				sx9500_irq_handler, sx9500_irq_thread_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				SX9500_IRQ_NAME, indio_dev);
		if (ret < 0)
			return ret;

		data->trig = devm_iio_trigger_alloc(&client->dev,
				"%s-dev%d", indio_dev->name, indio_dev->id);
		if (!data->trig)
			return -ENOMEM;

		data->trig->dev.parent = &client->dev;
		data->trig->ops = &sx9500_trigger_ops;
		iio_trigger_set_drvdata(data->trig, indio_dev);

		ret = iio_trigger_register(data->trig);
		if (ret)
			return ret;
	}

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 sx9500_trigger_handler,
					 &sx9500_buffer_setup_ops);
	if (ret < 0)
		goto out_trigger_unregister;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto out_buffer_cleanup;

	return 0;

out_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
out_trigger_unregister:
	if (client->irq > 0)
		iio_trigger_unregister(data->trig);

	return ret;
}