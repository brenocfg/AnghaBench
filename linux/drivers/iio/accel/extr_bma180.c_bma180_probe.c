#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct i2c_device_id {int driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_19__ {scalar_t__ of_node; } ;
struct i2c_client {scalar_t__ irq; TYPE_3__ dev; } ;
struct bma180_data {TYPE_15__* part_info; TYPE_4__* trig; int /*<<< orphan*/  mutex; int /*<<< orphan*/  orientation; struct i2c_client* client; } ;
typedef  enum chip_ids { ____Placeholder_chip_ids } chip_ids ;
struct TYPE_18__ {TYPE_3__* parent; } ;
struct TYPE_20__ {int /*<<< orphan*/ * ops; TYPE_2__ dev; } ;
struct TYPE_16__ {int (* chip_config ) (struct bma180_data*) ;int /*<<< orphan*/  (* chip_disable ) (struct bma180_data*) ;int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  bma180_info ; 
 TYPE_15__* bma180_part_info ; 
 int /*<<< orphan*/  bma180_trigger_handler ; 
 int /*<<< orphan*/  bma180_trigger_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int devm_request_irq (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct bma180_data* iio_priv (struct iio_dev*) ; 
 int iio_read_mount_matrix (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 TYPE_4__* iio_trigger_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_free (TYPE_4__*) ; 
 int /*<<< orphan*/  iio_trigger_generic_data_rdy_poll ; 
 int /*<<< orphan*/  iio_trigger_get (TYPE_4__*) ; 
 int iio_trigger_register (TYPE_4__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_4__*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (TYPE_4__*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (TYPE_3__*) ; 
 int stub1 (struct bma180_data*) ; 
 int /*<<< orphan*/  stub2 (struct bma180_data*) ; 

__attribute__((used)) static int bma180_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct bma180_data *data;
	struct iio_dev *indio_dev;
	enum chip_ids chip;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	if (client->dev.of_node)
		chip = (enum chip_ids)of_device_get_match_data(&client->dev);
	else
		chip = id->driver_data;
	data->part_info = &bma180_part_info[chip];

	ret = iio_read_mount_matrix(&client->dev, "mount-matrix",
				&data->orientation);
	if (ret)
		return ret;

	ret = data->part_info->chip_config(data);
	if (ret < 0)
		goto err_chip_disable;

	mutex_init(&data->mutex);
	indio_dev->dev.parent = &client->dev;
	indio_dev->channels = data->part_info->channels;
	indio_dev->num_channels = data->part_info->num_channels;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &bma180_info;

	if (client->irq > 0) {
		data->trig = iio_trigger_alloc("%s-dev%d", indio_dev->name,
			indio_dev->id);
		if (!data->trig) {
			ret = -ENOMEM;
			goto err_chip_disable;
		}

		ret = devm_request_irq(&client->dev, client->irq,
			iio_trigger_generic_data_rdy_poll, IRQF_TRIGGER_RISING,
			"bma180_event", data->trig);
		if (ret) {
			dev_err(&client->dev, "unable to request IRQ\n");
			goto err_trigger_free;
		}

		data->trig->dev.parent = &client->dev;
		data->trig->ops = &bma180_trigger_ops;
		iio_trigger_set_drvdata(data->trig, indio_dev);
		indio_dev->trig = iio_trigger_get(data->trig);

		ret = iio_trigger_register(data->trig);
		if (ret)
			goto err_trigger_free;
	}

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
			bma180_trigger_handler, NULL);
	if (ret < 0) {
		dev_err(&client->dev, "unable to setup iio triggered buffer\n");
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
	if (data->trig)
		iio_trigger_unregister(data->trig);
err_trigger_free:
	iio_trigger_free(data->trig);
err_chip_disable:
	data->part_info->chip_disable(data);

	return ret;
}