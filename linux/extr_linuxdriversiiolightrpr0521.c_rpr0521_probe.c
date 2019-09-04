#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpr0521_data {TYPE_3__* drdy_trigger0; int /*<<< orphan*/  lock; struct regmap* regmap; struct i2c_client* client; } ;
struct regmap {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {TYPE_2__ dev; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  RPR0521_DRV_NAME ; 
 int /*<<< orphan*/  RPR0521_IRQ_NAME ; 
 int /*<<< orphan*/  RPR0521_SLEEP_DELAY_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ *,struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct rpr0521_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_3__*,struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpr0521_available_scan_masks ; 
 int /*<<< orphan*/  rpr0521_buffer_setup_ops ; 
 int /*<<< orphan*/  rpr0521_channels ; 
 int /*<<< orphan*/  rpr0521_drdy_irq_handler ; 
 int /*<<< orphan*/  rpr0521_drdy_irq_thread ; 
 int /*<<< orphan*/  rpr0521_info ; 
 int rpr0521_init (struct rpr0521_data*) ; 
 int /*<<< orphan*/  rpr0521_poweroff (struct rpr0521_data*) ; 
 int /*<<< orphan*/  rpr0521_regmap_config ; 
 int /*<<< orphan*/  rpr0521_trigger_consumer_handler ; 
 int /*<<< orphan*/  rpr0521_trigger_consumer_store_time ; 
 int /*<<< orphan*/  rpr0521_trigger_ops ; 

__attribute__((used)) static int rpr0521_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct rpr0521_data *data;
	struct iio_dev *indio_dev;
	struct regmap *regmap;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &rpr0521_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "regmap_init failed!\n");
		return PTR_ERR(regmap);
	}

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;

	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &rpr0521_info;
	indio_dev->name = RPR0521_DRV_NAME;
	indio_dev->channels = rpr0521_channels;
	indio_dev->num_channels = ARRAY_SIZE(rpr0521_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = rpr0521_init(data);
	if (ret < 0) {
		dev_err(&client->dev, "rpr0521 chip init failed\n");
		return ret;
	}

	ret = pm_runtime_set_active(&client->dev);
	if (ret < 0)
		goto err_poweroff;

	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev, RPR0521_SLEEP_DELAY_MS);
	pm_runtime_use_autosuspend(&client->dev);

	/*
	 * If sensor write/read is needed in _probe after _use_autosuspend,
	 * sensor needs to be _resumed first using rpr0521_set_power_state().
	 */

	/* IRQ to trigger setup */
	if (client->irq) {
		/* Trigger0 producer setup */
		data->drdy_trigger0 = devm_iio_trigger_alloc(
			indio_dev->dev.parent,
			"%s-dev%d", indio_dev->name, indio_dev->id);
		if (!data->drdy_trigger0) {
			ret = -ENOMEM;
			goto err_pm_disable;
		}
		data->drdy_trigger0->dev.parent = indio_dev->dev.parent;
		data->drdy_trigger0->ops = &rpr0521_trigger_ops;
		indio_dev->available_scan_masks = rpr0521_available_scan_masks;
		iio_trigger_set_drvdata(data->drdy_trigger0, indio_dev);

		/* Ties irq to trigger producer handler. */
		ret = devm_request_threaded_irq(&client->dev, client->irq,
			rpr0521_drdy_irq_handler, rpr0521_drdy_irq_thread,
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			RPR0521_IRQ_NAME, indio_dev);
		if (ret < 0) {
			dev_err(&client->dev, "request irq %d for trigger0 failed\n",
				client->irq);
			goto err_pm_disable;
			}

		ret = devm_iio_trigger_register(indio_dev->dev.parent,
						data->drdy_trigger0);
		if (ret) {
			dev_err(&client->dev, "iio trigger register failed\n");
			goto err_pm_disable;
		}

		/*
		 * Now whole pipe from physical interrupt (irq defined by
		 * devicetree to device) to trigger0 output is set up.
		 */

		/* Trigger consumer setup */
		ret = devm_iio_triggered_buffer_setup(indio_dev->dev.parent,
			indio_dev,
			rpr0521_trigger_consumer_store_time,
			rpr0521_trigger_consumer_handler,
			&rpr0521_buffer_setup_ops);
		if (ret < 0) {
			dev_err(&client->dev, "iio triggered buffer setup failed\n");
			goto err_pm_disable;
		}
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto err_pm_disable;

	return 0;

err_pm_disable:
	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);
	pm_runtime_put_noidle(&client->dev);
err_poweroff:
	rpr0521_poweroff(data);

	return ret;
}