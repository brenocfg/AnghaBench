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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; TYPE_1__ dev; void* num_channels; void* channels; } ;
struct ad8366_state {int type; int /*<<< orphan*/  reg; int /*<<< orphan*/ * info; int /*<<< orphan*/  reset_gpio; struct spi_device* spi; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
#define  ID_AD8366 130 
#define  ID_ADA4961 129 
#define  ID_ADL5240 128 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 void* ad8366_channels ; 
 int /*<<< orphan*/  ad8366_info ; 
 int /*<<< orphan*/ * ad8366_infos ; 
 int ad8366_write (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ada4961_channels ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad8366_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad8366_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct ad8366_state *st;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (indio_dev == NULL)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get(&spi->dev, "vcc");
	if (!IS_ERR(st->reg)) {
		ret = regulator_enable(st->reg);
		if (ret)
			return ret;
	}

	spi_set_drvdata(spi, indio_dev);
	mutex_init(&st->lock);
	st->spi = spi;
	st->type = spi_get_device_id(spi)->driver_data;

	switch (st->type) {
	case ID_AD8366:
		indio_dev->channels = ad8366_channels;
		indio_dev->num_channels = ARRAY_SIZE(ad8366_channels);
		break;
	case ID_ADA4961:
	case ID_ADL5240:
		st->reset_gpio = devm_gpiod_get(&spi->dev, "reset",
			GPIOD_OUT_HIGH);
		indio_dev->channels = ada4961_channels;
		indio_dev->num_channels = ARRAY_SIZE(ada4961_channels);
		break;
	default:
		dev_err(&spi->dev, "Invalid device ID\n");
		ret = -EINVAL;
		goto error_disable_reg;
	}

	st->info = &ad8366_infos[st->type];
	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad8366_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = ad8366_write(indio_dev, 0 , 0);
	if (ret < 0)
		goto error_disable_reg;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_disable_reg;

	return 0;

error_disable_reg:
	if (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	return ret;
}