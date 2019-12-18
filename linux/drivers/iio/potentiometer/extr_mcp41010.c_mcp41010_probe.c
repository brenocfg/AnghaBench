#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct spi_device {struct device dev; } ;
struct mcp41010_data {TYPE_3__* cfg; int /*<<< orphan*/  lock; struct spi_device* spi; } ;
struct TYPE_5__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  wipers; } ;
struct TYPE_6__ {size_t driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 struct mcp41010_data* iio_priv (struct iio_dev*) ; 
 TYPE_3__* mcp41010_cfg ; 
 int /*<<< orphan*/  mcp41010_channels ; 
 int /*<<< orphan*/  mcp41010_info ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* of_device_get_match_data (struct device*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int mcp41010_probe(struct spi_device *spi)
{
	int err;
	struct device *dev = &spi->dev;
	struct mcp41010_data *data;
	struct iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);
	data->spi = spi;
	data->cfg = of_device_get_match_data(&spi->dev);
	if (!data->cfg)
		data->cfg = &mcp41010_cfg[spi_get_device_id(spi)->driver_data];

	mutex_init(&data->lock);

	indio_dev->dev.parent = dev;
	indio_dev->info = &mcp41010_info;
	indio_dev->channels = mcp41010_channels;
	indio_dev->num_channels = data->cfg->wipers;
	indio_dev->name = data->cfg->name;

	err = devm_iio_device_register(dev, indio_dev);
	if (err)
		dev_info(&spi->dev, "Unable to register %s\n", indio_dev->name);

	return err;
}