#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct of_device_id {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int modes; TYPE_2__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {size_t driver_data; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct atlas_device {int (* calibration ) (struct atlas_data*) ;int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;
struct atlas_data {struct iio_trigger* trig; int /*<<< orphan*/  work; int /*<<< orphan*/  regmap; struct atlas_device* chip; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATLAS_DRV_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int INDIO_BUFFER_SOFTWARE ; 
 int INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atlas_buffer_setup_ops ; 
 struct atlas_device* atlas_devices ; 
 int /*<<< orphan*/  atlas_dt_ids ; 
 int /*<<< orphan*/  atlas_info ; 
 int /*<<< orphan*/  atlas_interrupt_handler ; 
 int /*<<< orphan*/  atlas_interrupt_trigger_ops ; 
 int /*<<< orphan*/  atlas_regmap_config ; 
 int atlas_set_powermode (struct atlas_data*,int) ; 
 int /*<<< orphan*/  atlas_trigger_handler ; 
 int /*<<< orphan*/  atlas_work_handler ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 struct iio_trigger* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct atlas_data* iio_priv (struct iio_dev*) ; 
 int iio_trigger_register (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int stub1 (struct atlas_data*) ; 

__attribute__((used)) static int atlas_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct atlas_data *data;
	struct atlas_device *chip;
	const struct of_device_id *of_id;
	struct iio_trigger *trig;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	of_id = of_match_device(atlas_dt_ids, &client->dev);
	if (!of_id)
		chip = &atlas_devices[id->driver_data];
	else
		chip = &atlas_devices[(unsigned long)of_id->data];

	indio_dev->info = &atlas_info;
	indio_dev->name = ATLAS_DRV_NAME;
	indio_dev->channels = chip->channels;
	indio_dev->num_channels = chip->num_channels;
	indio_dev->modes = INDIO_BUFFER_SOFTWARE | INDIO_DIRECT_MODE;
	indio_dev->dev.parent = &client->dev;

	trig = devm_iio_trigger_alloc(&client->dev, "%s-dev%d",
				      indio_dev->name, indio_dev->id);

	if (!trig)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	data->trig = trig;
	data->chip = chip;
	trig->dev.parent = indio_dev->dev.parent;
	trig->ops = &atlas_interrupt_trigger_ops;
	iio_trigger_set_drvdata(trig, indio_dev);

	i2c_set_clientdata(client, indio_dev);

	data->regmap = devm_regmap_init_i2c(client, &atlas_regmap_config);
	if (IS_ERR(data->regmap)) {
		dev_err(&client->dev, "regmap initialization failed\n");
		return PTR_ERR(data->regmap);
	}

	ret = pm_runtime_set_active(&client->dev);
	if (ret)
		return ret;

	if (client->irq <= 0) {
		dev_err(&client->dev, "no valid irq defined\n");
		return -EINVAL;
	}

	ret = chip->calibration(data);
	if (ret)
		return ret;

	ret = iio_trigger_register(trig);
	if (ret) {
		dev_err(&client->dev, "failed to register trigger\n");
		return ret;
	}

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_time,
		&atlas_trigger_handler, &atlas_buffer_setup_ops);
	if (ret) {
		dev_err(&client->dev, "cannot setup iio trigger\n");
		goto unregister_trigger;
	}

	init_irq_work(&data->work, atlas_work_handler);

	/* interrupt pin toggles on new conversion */
	ret = devm_request_threaded_irq(&client->dev, client->irq,
					NULL, atlas_interrupt_handler,
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"atlas_irq",
					indio_dev);
	if (ret) {
		dev_err(&client->dev, "request irq (%d) failed\n", client->irq);
		goto unregister_buffer;
	}

	ret = atlas_set_powermode(data, 1);
	if (ret) {
		dev_err(&client->dev, "cannot power device on");
		goto unregister_buffer;
	}

	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev, 2500);
	pm_runtime_use_autosuspend(&client->dev);

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&client->dev, "unable to register device\n");
		goto unregister_pm;
	}

	return 0;

unregister_pm:
	pm_runtime_disable(&client->dev);
	atlas_set_powermode(data, 0);

unregister_buffer:
	iio_triggered_buffer_cleanup(indio_dev);

unregister_trigger:
	iio_trigger_unregister(data->trig);

	return ret;
}