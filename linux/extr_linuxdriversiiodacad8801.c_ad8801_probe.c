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
struct spi_device_id {scalar_t__ driver_data; int /*<<< orphan*/  name; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct ad8801_state {int vrefh_mv; int vrefl_mv; int /*<<< orphan*/ * vrefh_reg; int /*<<< orphan*/ * vrefl_reg; struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 scalar_t__ ID_AD8803 ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ad8801_channels ; 
 int /*<<< orphan*/  ad8801_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 void* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad8801_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int regulator_get_voltage (int /*<<< orphan*/ *) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad8801_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct ad8801_state *state;
	const struct spi_device_id *id;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*state));
	if (indio_dev == NULL)
		return -ENOMEM;

	state = iio_priv(indio_dev);
	state->spi = spi;
	id = spi_get_device_id(spi);

	state->vrefh_reg = devm_regulator_get(&spi->dev, "vrefh");
	if (IS_ERR(state->vrefh_reg)) {
		dev_err(&spi->dev, "Vrefh regulator not specified\n");
		return PTR_ERR(state->vrefh_reg);
	}

	ret = regulator_enable(state->vrefh_reg);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable vrefh regulator: %d\n",
				ret);
		return ret;
	}

	ret = regulator_get_voltage(state->vrefh_reg);
	if (ret < 0) {
		dev_err(&spi->dev, "Failed to read vrefh regulator: %d\n",
				ret);
		goto error_disable_vrefh_reg;
	}
	state->vrefh_mv = ret / 1000;

	if (id->driver_data == ID_AD8803) {
		state->vrefl_reg = devm_regulator_get(&spi->dev, "vrefl");
		if (IS_ERR(state->vrefl_reg)) {
			dev_err(&spi->dev, "Vrefl regulator not specified\n");
			ret = PTR_ERR(state->vrefl_reg);
			goto error_disable_vrefh_reg;
		}

		ret = regulator_enable(state->vrefl_reg);
		if (ret) {
			dev_err(&spi->dev, "Failed to enable vrefl regulator: %d\n",
					ret);
			goto error_disable_vrefh_reg;
		}

		ret = regulator_get_voltage(state->vrefl_reg);
		if (ret < 0) {
			dev_err(&spi->dev, "Failed to read vrefl regulator: %d\n",
					ret);
			goto error_disable_vrefl_reg;
		}
		state->vrefl_mv = ret / 1000;
	} else {
		state->vrefl_mv = 0;
		state->vrefl_reg = NULL;
	}

	spi_set_drvdata(spi, indio_dev);
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &ad8801_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ad8801_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad8801_channels);
	indio_dev->name = id->name;

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&spi->dev, "Failed to register iio device: %d\n",
				ret);
		goto error_disable_vrefl_reg;
	}

	return 0;

error_disable_vrefl_reg:
	if (state->vrefl_reg)
		regulator_disable(state->vrefl_reg);
error_disable_vrefh_reg:
	regulator_disable(state->vrefh_reg);
	return ret;
}