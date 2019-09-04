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
struct spi_device {int dummy; } ;
struct iio_dev {int dummy; } ;
struct ad5764_state {int /*<<< orphan*/  vref_reg; TYPE_1__* chip_info; } ;
struct TYPE_2__ {scalar_t__ int_vref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ad5764_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iio_dev* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int ad5764_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct ad5764_state *st = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	if (st->chip_info->int_vref == 0)
		regulator_bulk_disable(ARRAY_SIZE(st->vref_reg), st->vref_reg);

	return 0;
}