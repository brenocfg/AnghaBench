#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct ad5755_platform_data* platform_data; scalar_t__ of_node; } ;
struct spi_device {TYPE_3__ dev; } ;
struct TYPE_9__ {TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct ad5755_state {int pwr_down; struct spi_device* spi; int /*<<< orphan*/ * chip_info; } ;
struct ad5755_platform_data {int dummy; } ;
typedef  enum ad5755_type { ____Placeholder_ad5755_type } ad5755_type ;
struct TYPE_10__ {int driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5755_NUM_CHANNELS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/ * ad5755_chip_info_tbl ; 
 struct ad5755_platform_data ad5755_default_pdata ; 
 int /*<<< orphan*/  ad5755_info ; 
 int ad5755_init_channels (struct iio_dev*,struct ad5755_platform_data const*) ; 
 struct ad5755_platform_data* ad5755_parse_dt (TYPE_3__*) ; 
 int ad5755_setup_pdata (struct iio_dev*,struct ad5755_platform_data const*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct ad5755_platform_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int devm_iio_device_register (TYPE_3__*,struct iio_dev*) ; 
 struct ad5755_state* iio_priv (struct iio_dev*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad5755_probe(struct spi_device *spi)
{
	enum ad5755_type type = spi_get_device_id(spi)->driver_data;
	const struct ad5755_platform_data *pdata = dev_get_platdata(&spi->dev);
	struct iio_dev *indio_dev;
	struct ad5755_state *st;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (indio_dev == NULL) {
		dev_err(&spi->dev, "Failed to allocate iio device\n");
		return  -ENOMEM;
	}

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->chip_info = &ad5755_chip_info_tbl[type];
	st->spi = spi;
	st->pwr_down = 0xf;

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5755_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->num_channels = AD5755_NUM_CHANNELS;

	if (spi->dev.of_node)
		pdata = ad5755_parse_dt(&spi->dev);
	else
		pdata = spi->dev.platform_data;

	if (!pdata) {
		dev_warn(&spi->dev, "no platform data? using default\n");
		pdata = &ad5755_default_pdata;
	}

	ret = ad5755_init_channels(indio_dev, pdata);
	if (ret)
		return ret;

	ret = ad5755_setup_pdata(indio_dev, pdata);
	if (ret)
		return ret;

	return devm_iio_device_register(&spi->dev, indio_dev);
}