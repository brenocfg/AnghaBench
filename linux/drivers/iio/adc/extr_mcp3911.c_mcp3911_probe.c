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
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_3__ dev; } ;
struct mcp3911 {int /*<<< orphan*/ * vref; int /*<<< orphan*/ * clki; int /*<<< orphan*/  lock; struct spi_device* spi; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (TYPE_3__*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct mcp3911* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mcp3911_channels ; 
 int mcp3911_config (struct mcp3911*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcp3911_info ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int mcp3911_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct mcp3911 *adc;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*adc));
	if (!indio_dev)
		return -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;

	adc->vref = devm_regulator_get_optional(&adc->spi->dev, "vref");
	if (IS_ERR(adc->vref)) {
		if (PTR_ERR(adc->vref) == -ENODEV) {
			adc->vref = NULL;
		} else {
			dev_err(&adc->spi->dev,
				"failed to get regulator (%ld)\n",
				PTR_ERR(adc->vref));
			return PTR_ERR(adc->vref);
		}

	} else {
		ret = regulator_enable(adc->vref);
		if (ret)
			return ret;
	}

	adc->clki = devm_clk_get(&adc->spi->dev, NULL);
	if (IS_ERR(adc->clki)) {
		if (PTR_ERR(adc->clki) == -ENOENT) {
			adc->clki = NULL;
		} else {
			dev_err(&adc->spi->dev,
				"failed to get adc clk (%ld)\n",
				PTR_ERR(adc->clki));
			ret = PTR_ERR(adc->clki);
			goto reg_disable;
		}
	} else {
		ret = clk_prepare_enable(adc->clki);
		if (ret < 0) {
			dev_err(&adc->spi->dev,
				"Failed to enable clki: %d\n", ret);
			goto reg_disable;
		}
	}

	ret = mcp3911_config(adc, spi->dev.of_node);
	if (ret)
		goto clk_disable;

	indio_dev->dev.parent = &spi->dev;
	indio_dev->dev.of_node = spi->dev.of_node;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &mcp3911_info;
	spi_set_drvdata(spi, indio_dev);

	indio_dev->channels = mcp3911_channels;
	indio_dev->num_channels = ARRAY_SIZE(mcp3911_channels);

	mutex_init(&adc->lock);

	ret = iio_device_register(indio_dev);
	if (ret)
		goto clk_disable;

	return ret;

clk_disable:
	clk_disable_unprepare(adc->clki);
reg_disable:
	if (adc->vref)
		regulator_disable(adc->vref);

	return ret;
}