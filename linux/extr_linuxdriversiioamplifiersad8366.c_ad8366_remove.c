#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct spi_device {int dummy; } ;
struct regulator {int dummy; } ;
struct iio_dev {int dummy; } ;
struct ad8366_state {struct regulator* reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct regulator*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ad8366_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (struct regulator*) ; 
 struct iio_dev* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int ad8366_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct ad8366_state *st = iio_priv(indio_dev);
	struct regulator *reg = st->reg;

	iio_device_unregister(indio_dev);

	if (!IS_ERR(reg))
		regulator_disable(reg);

	return 0;
}