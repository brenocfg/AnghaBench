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
struct TYPE_2__ {struct ad7793_platform_data* platform_data; } ;
struct spi_device {TYPE_1__ dev; } ;
struct iio_dev {int dummy; } ;
struct ad7793_state {int /*<<< orphan*/  reg; } ;
struct ad7793_platform_data {scalar_t__ refsel; } ;

/* Variables and functions */
 scalar_t__ AD7793_REFSEL_INTERNAL ; 
 int /*<<< orphan*/  ad_sd_cleanup_buffer_and_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ad7793_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct iio_dev* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int ad7793_remove(struct spi_device *spi)
{
	const struct ad7793_platform_data *pdata = spi->dev.platform_data;
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct ad7793_state *st = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	ad_sd_cleanup_buffer_and_trigger(indio_dev);

	if (pdata->refsel != AD7793_REFSEL_INTERNAL)
		regulator_disable(st->reg);

	return 0;
}