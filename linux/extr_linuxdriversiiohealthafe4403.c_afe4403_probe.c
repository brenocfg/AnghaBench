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
struct spi_device {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; int /*<<< orphan*/  modes; } ;
struct afe4403_data {scalar_t__ irq; int /*<<< orphan*/  regulator; TYPE_3__* trig; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * fields; struct spi_device* spi; } ;
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {TYPE_2__ dev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE4403_DRIVER_NAME ; 
 int /*<<< orphan*/  AFE440X_CONTROL0 ; 
 int /*<<< orphan*/  AFE440X_CONTROL0_SW_RESET ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int F_MAX_FIELDS ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afe4403_channels ; 
 int /*<<< orphan*/  afe4403_iio_info ; 
 int /*<<< orphan*/ * afe4403_reg_fields ; 
 int /*<<< orphan*/  afe4403_reg_sequences ; 
 int /*<<< orphan*/  afe4403_regmap_config ; 
 int /*<<< orphan*/  afe4403_trigger_handler ; 
 int /*<<< orphan*/  afe4403_trigger_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_field_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct afe4403_data* iio_priv (struct iio_dev*) ; 
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
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int afe4403_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct afe4403_data *afe;
	int i, ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*afe));
	if (!indio_dev)
		return -ENOMEM;

	afe = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	afe->dev = &spi->dev;
	afe->spi = spi;
	afe->irq = spi->irq;

	afe->regmap = devm_regmap_init_spi(spi, &afe4403_regmap_config);
	if (IS_ERR(afe->regmap)) {
		dev_err(afe->dev, "Unable to allocate register map\n");
		return PTR_ERR(afe->regmap);
	}

	for (i = 0; i < F_MAX_FIELDS; i++) {
		afe->fields[i] = devm_regmap_field_alloc(afe->dev, afe->regmap,
							 afe4403_reg_fields[i]);
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
		goto err_disable_reg;
	}

	ret = regmap_multi_reg_write(afe->regmap, afe4403_reg_sequences,
				     ARRAY_SIZE(afe4403_reg_sequences));
	if (ret) {
		dev_err(afe->dev, "Unable to set register defaults\n");
		goto err_disable_reg;
	}

	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->dev.parent = afe->dev;
	indio_dev->channels = afe4403_channels;
	indio_dev->num_channels = ARRAY_SIZE(afe4403_channels);
	indio_dev->name = AFE4403_DRIVER_NAME;
	indio_dev->info = &afe4403_iio_info;

	if (afe->irq > 0) {
		afe->trig = devm_iio_trigger_alloc(afe->dev,
						   "%s-dev%d",
						   indio_dev->name,
						   indio_dev->id);
		if (!afe->trig) {
			dev_err(afe->dev, "Unable to allocate IIO trigger\n");
			ret = -ENOMEM;
			goto err_disable_reg;
		}

		iio_trigger_set_drvdata(afe->trig, indio_dev);

		afe->trig->ops = &afe4403_trigger_ops;
		afe->trig->dev.parent = afe->dev;

		ret = iio_trigger_register(afe->trig);
		if (ret) {
			dev_err(afe->dev, "Unable to register IIO trigger\n");
			goto err_disable_reg;
		}

		ret = devm_request_threaded_irq(afe->dev, afe->irq,
						iio_trigger_generic_data_rdy_poll,
						NULL, IRQF_ONESHOT,
						AFE4403_DRIVER_NAME,
						afe->trig);
		if (ret) {
			dev_err(afe->dev, "Unable to request IRQ\n");
			goto err_trig;
		}
	}

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_time,
					 afe4403_trigger_handler, NULL);
	if (ret) {
		dev_err(afe->dev, "Unable to setup buffer\n");
		goto err_trig;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(afe->dev, "Unable to register IIO device\n");
		goto err_buff;
	}

	return 0;

err_buff:
	iio_triggered_buffer_cleanup(indio_dev);
err_trig:
	if (afe->irq > 0)
		iio_trigger_unregister(afe->trig);
err_disable_reg:
	regulator_disable(afe->regulator);

	return ret;
}