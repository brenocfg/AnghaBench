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
struct spi_device {int /*<<< orphan*/  mode; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct ad2s1210_state {int hysteresis; int resolution; int /*<<< orphan*/  fclkin; int /*<<< orphan*/  fexcit; int /*<<< orphan*/  mode; struct spi_device* sdev; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD2S1210_DEF_EXCIT ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  MOD_CONFIG ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  ad2s1210_channels ; 
 int /*<<< orphan*/  ad2s1210_info ; 
 int /*<<< orphan*/  ad2s1210_initial (struct ad2s1210_state*) ; 
 int ad2s1210_setup_gpios (struct ad2s1210_state*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 struct ad2s1210_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  spi_setup (struct spi_device*) ; 

__attribute__((used)) static int ad2s1210_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct ad2s1210_state *st;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;
	st = iio_priv(indio_dev);
	ret = ad2s1210_setup_gpios(st);
	if (ret < 0)
		return ret;

	spi_set_drvdata(spi, indio_dev);

	mutex_init(&st->lock);
	st->sdev = spi;
	st->hysteresis = true;
	st->mode = MOD_CONFIG;
	st->resolution = 12;
	st->fexcit = AD2S1210_DEF_EXCIT;

	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &ad2s1210_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ad2s1210_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad2s1210_channels);
	indio_dev->name = spi_get_device_id(spi)->name;

	ret = devm_iio_device_register(&spi->dev, indio_dev);
	if (ret)
		return ret;

	st->fclkin = spi->max_speed_hz;
	spi->mode = SPI_MODE_3;
	spi_setup(spi);
	ad2s1210_initial(st);

	return 0;
}