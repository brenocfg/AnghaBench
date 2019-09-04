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
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; int /*<<< orphan*/  max_speed_hz; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct ad2s1200_state {void* rdvel; void* sample; struct spi_device* sdev; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD2S1200_HZ ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  ad2s1200_channels ; 
 int /*<<< orphan*/  ad2s1200_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 struct ad2s1200_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int ad2s1200_probe(struct spi_device *spi)
{
	struct ad2s1200_state *st;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	spi_set_drvdata(spi, indio_dev);
	st = iio_priv(indio_dev);
	mutex_init(&st->lock);
	st->sdev = spi;

	st->sample = devm_gpiod_get(&spi->dev, "adi,sample", GPIOD_OUT_LOW);
	if (IS_ERR(st->sample)) {
		dev_err(&spi->dev, "Failed to claim SAMPLE gpio: err=%ld\n",
			PTR_ERR(st->sample));
		return PTR_ERR(st->sample);
	}

	st->rdvel = devm_gpiod_get(&spi->dev, "adi,rdvel", GPIOD_OUT_LOW);
	if (IS_ERR(st->rdvel)) {
		dev_err(&spi->dev, "Failed to claim RDVEL gpio: err=%ld\n",
			PTR_ERR(st->rdvel));
		return PTR_ERR(st->rdvel);
	}

	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &ad2s1200_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ad2s1200_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad2s1200_channels);
	indio_dev->name = spi_get_device_id(spi)->name;

	spi->max_speed_hz = AD2S1200_HZ;
	spi->mode = SPI_MODE_3;
	ret = spi_setup(spi);

	if (ret < 0) {
		dev_err(&spi->dev, "spi_setup failed!\n");
		return ret;
	}

	return devm_iio_device_register(&spi->dev, indio_dev);
}