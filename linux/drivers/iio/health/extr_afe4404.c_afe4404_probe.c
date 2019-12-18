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
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; int /*<<< orphan*/  modes; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct afe4404_data {scalar_t__ irq; int /*<<< orphan*/  regulator; TYPE_3__* trig; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * fields; } ;
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {TYPE_2__ dev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE4404_DRIVER_NAME ; 
 int /*<<< orphan*/  AFE440X_CONTROL0 ; 
 int /*<<< orphan*/  AFE440X_CONTROL0_SW_RESET ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int F_MAX_FIELDS ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afe4404_channels ; 
 int /*<<< orphan*/  afe4404_iio_info ; 
 int /*<<< orphan*/ * afe4404_reg_fields ; 
 int /*<<< orphan*/  afe4404_reg_sequences ; 
 int /*<<< orphan*/  afe4404_regmap_config ; 
 int /*<<< orphan*/  afe4404_trigger_handler ; 
 int /*<<< orphan*/  afe4404_trigger_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_field_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct afe4404_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_generic_data_rdy_poll ; 
 int iio_trigger_register (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_3__*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afe4404_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct afe4404_data *afe;
	int i, ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*afe));
	if (!indio_dev)
		return -ENOMEM;

	afe = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	afe->dev = &client->dev;
	afe->irq = client->irq;

	afe->regmap = devm_regmap_init_i2c(client, &afe4404_regmap_config);
	if (IS_ERR(afe->regmap)) {
		dev_err(afe->dev, "Unable to allocate register map\n");
		return PTR_ERR(afe->regmap);
	}

	for (i = 0; i < F_MAX_FIELDS; i++) {
		afe->fields[i] = devm_regmap_field_alloc(afe->dev, afe->regmap,
							 afe4404_reg_fields[i]);
		if (IS_ERR(afe->fields[i])) {
			dev_err(afe->dev, "Unable to allocate regmap fields\n");
			return PTR_ERR(afe->fields[i]);
		}
	}

	afe->regulator = devm_regulator_get(afe->dev, "tx_sup");
	if (IS_ERR(afe->regulator)) {
		dev_err(afe->dev, "Unable to get regulator\n");
		return PTR_ERR(afe->regulator);
	}
	ret = regulator_enable(afe->regulator);
	if (ret) {
		dev_err(afe->dev, "Unable to enable regulator\n");
		return ret;
	}

	ret = regmap_write(afe->regmap, AFE440X_CONTROL0,
			   AFE440X_CONTROL0_SW_RESET);
	if (ret) {
		dev_err(afe->dev, "Unable to reset device\n");
		goto disable_reg;
	}

	ret = regmap_multi_reg_write(afe->regmap, afe4404_reg_sequences,
				     ARRAY_SIZE(afe4404_reg_sequences));
	if (ret) {
		dev_err(afe->dev, "Unable to set register defaults\n");
		goto disable_reg;
	}

	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->dev.parent = afe->dev;
	indio_dev->channels = afe4404_channels;
	indio_dev->num_channels = ARRAY_SIZE(afe4404_channels);
	indio_dev->name = AFE4404_DRIVER_NAME;
	indio_dev->info = &afe4404_iio_info;

	if (afe->irq > 0) {
		afe->trig = devm_iio_trigger_alloc(afe->dev,
						   "%s-dev%d",
						   indio_dev->name,
						   indio_dev->id);
		if (!afe->trig) {
			dev_err(afe->dev, "Unable to allocate IIO trigger\n");
			ret = -ENOMEM;
			goto disable_reg;
		}

		iio_trigger_set_drvdata(afe->trig, indio_dev);

		afe->trig->ops = &afe4404_trigger_ops;
		afe->trig->dev.parent = afe->dev;

		ret = iio_trigger_register(afe->trig);
		if (ret) {
			dev_err(afe->dev, "Unable to register IIO trigger\n");
			goto disable_reg;
		}

		ret = devm_request_threaded_irq(afe->dev, afe->irq,
						iio_trigger_generic_data_rdy_poll,
						NULL, IRQF_ONESHOT,
						AFE4404_DRIVER_NAME,
						afe->trig);
		if (ret) {
			dev_err(afe->dev, "Unable to request IRQ\n");
			goto disable_reg;
		}
	}

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_time,
					 afe4404_trigger_handler, NULL);
	if (ret) {
		dev_err(afe->dev, "Unable to setup buffer\n");
		goto unregister_trigger;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(afe->dev, "Unable to register IIO device\n");
		goto unregister_triggered_buffer;
	}

	return 0;

unregister_triggered_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
unregister_trigger:
	if (afe->irq > 0)
		iio_trigger_unregister(afe->trig);
disable_reg:
	regulator_disable(afe->regulator);

	return ret;
}