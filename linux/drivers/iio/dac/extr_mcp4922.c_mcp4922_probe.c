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
struct spi_device_id {size_t driver_data; int /*<<< orphan*/  name; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct mcp4922_state {int vref_mv; int /*<<< orphan*/  vref_reg; struct spi_device* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCP4922_NUM_CHANNELS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct mcp4922_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/ * mcp4922_channels ; 
 int /*<<< orphan*/  mcp4922_info ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int mcp4922_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct mcp4922_state *state;
	const struct spi_device_id *id;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*state));
	if (indio_dev == NULL)
		return -ENOMEM;

	state = iio_priv(indio_dev);
	state->spi = spi;
	state->vref_reg = devm_regulator_get(&spi->dev, "vref");
	if (IS_ERR(state->vref_reg)) {
		dev_err(&spi->dev, "Vref regulator not specified\n");
		return PTR_ERR(state->vref_reg);
	}

	ret = regulator_enable(state->vref_reg);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable vref regulator: %d\n",
				ret);
		return ret;
	}

	ret = regulator_get_voltage(state->vref_reg);
	if (ret < 0) {
		dev_err(&spi->dev, "Failed to read vref regulator: %d\n",
				ret);
		goto error_disable_reg;
	}
	state->vref_mv = ret / 1000;

	spi_set_drvdata(spi, indio_dev);
	id = spi_get_device_id(spi);
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &mcp4922_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = mcp4922_channels[id->driver_data];
	indio_dev->num_channels = MCP4922_NUM_CHANNELS;
	indio_dev->name = id->name;

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&spi->dev, "Failed to register iio device: %d\n",
				ret);
		goto error_disable_reg;
	}

	return 0;

error_disable_reg:
	regulator_disable(state->vref_reg);

	return ret;
}