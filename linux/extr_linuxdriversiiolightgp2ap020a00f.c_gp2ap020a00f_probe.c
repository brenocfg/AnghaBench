#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_11__ {struct TYPE_11__* parent; } ;
struct iio_dev {TYPE_4__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  irq; TYPE_4__ dev; } ;
struct gp2ap020a00f_data {struct regmap* vled_reg; TYPE_2__* trig; int /*<<< orphan*/  work; struct i2c_client* client; int /*<<< orphan*/  lock; int /*<<< orphan*/  data_ready_queue; struct regmap* regmap; int /*<<< orphan*/  cur_opmode; } ;
struct TYPE_9__ {TYPE_4__* parent; } ;
struct TYPE_10__ {TYPE_1__ dev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_SHUTDOWN ; 
 int /*<<< orphan*/  GP2AP020A00F_OP_REG ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_4__*,int) ; 
 TYPE_2__* devm_iio_trigger_alloc (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regmap* devm_regulator_get (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  gp2ap020a00f_buffer_setup_ops ; 
 int /*<<< orphan*/  gp2ap020a00f_channels ; 
 int /*<<< orphan*/  gp2ap020a00f_iio_trigger_work ; 
 int /*<<< orphan*/  gp2ap020a00f_info ; 
 int /*<<< orphan*/  gp2ap020a00f_reg_init_tab ; 
 int /*<<< orphan*/  gp2ap020a00f_regmap_config ; 
 int /*<<< orphan*/  gp2ap020a00f_thresh_event_handler ; 
 int /*<<< orphan*/  gp2ap020a00f_trigger_handler ; 
 int /*<<< orphan*/  gp2ap020a00f_trigger_ops ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct gp2ap020a00f_data* iio_priv (struct iio_dev*) ; 
 int iio_trigger_register (TYPE_2__*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int regmap_bulk_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (struct regmap*) ; 
 int regulator_enable (struct regmap*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,struct iio_dev*) ; 

__attribute__((used)) static int gp2ap020a00f_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct gp2ap020a00f_data *data;
	struct iio_dev *indio_dev;
	struct regmap *regmap;
	int err;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);

	data->vled_reg = devm_regulator_get(&client->dev, "vled");
	if (IS_ERR(data->vled_reg))
		return PTR_ERR(data->vled_reg);

	err = regulator_enable(data->vled_reg);
	if (err)
		return err;

	regmap = devm_regmap_init_i2c(client, &gp2ap020a00f_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "Regmap initialization failed.\n");
		err = PTR_ERR(regmap);
		goto error_regulator_disable;
	}

	/* Initialize device registers */
	err = regmap_bulk_write(regmap, GP2AP020A00F_OP_REG,
			gp2ap020a00f_reg_init_tab,
			ARRAY_SIZE(gp2ap020a00f_reg_init_tab));

	if (err < 0) {
		dev_err(&client->dev, "Device initialization failed.\n");
		goto error_regulator_disable;
	}

	i2c_set_clientdata(client, indio_dev);

	data->client = client;
	data->cur_opmode = GP2AP020A00F_OPMODE_SHUTDOWN;
	data->regmap = regmap;
	init_waitqueue_head(&data->data_ready_queue);

	mutex_init(&data->lock);
	indio_dev->dev.parent = &client->dev;
	indio_dev->channels = gp2ap020a00f_channels;
	indio_dev->num_channels = ARRAY_SIZE(gp2ap020a00f_channels);
	indio_dev->info = &gp2ap020a00f_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIRECT_MODE;

	/* Allocate buffer */
	err = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_time,
		&gp2ap020a00f_trigger_handler, &gp2ap020a00f_buffer_setup_ops);
	if (err < 0)
		goto error_regulator_disable;

	/* Allocate trigger */
	data->trig = devm_iio_trigger_alloc(&client->dev, "%s-trigger",
							indio_dev->name);
	if (data->trig == NULL) {
		err = -ENOMEM;
		dev_err(&indio_dev->dev, "Failed to allocate iio trigger.\n");
		goto error_uninit_buffer;
	}

	/* This needs to be requested here for read_raw calls to work. */
	err = request_threaded_irq(client->irq, NULL,
				   &gp2ap020a00f_thresh_event_handler,
				   IRQF_TRIGGER_FALLING |
				   IRQF_ONESHOT,
				   "gp2ap020a00f_als_event",
				   indio_dev);
	if (err < 0) {
		dev_err(&client->dev, "Irq request failed.\n");
		goto error_uninit_buffer;
	}

	data->trig->ops = &gp2ap020a00f_trigger_ops;
	data->trig->dev.parent = &data->client->dev;

	init_irq_work(&data->work, gp2ap020a00f_iio_trigger_work);

	err = iio_trigger_register(data->trig);
	if (err < 0) {
		dev_err(&client->dev, "Failed to register iio trigger.\n");
		goto error_free_irq;
	}

	err = iio_device_register(indio_dev);
	if (err < 0)
		goto error_trigger_unregister;

	return 0;

error_trigger_unregister:
	iio_trigger_unregister(data->trig);
error_free_irq:
	free_irq(client->irq, indio_dev);
error_uninit_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
error_regulator_disable:
	regulator_disable(data->vled_reg);

	return err;
}