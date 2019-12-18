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
struct mcp3911 {scalar_t__ vref; int /*<<< orphan*/  clki; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct mcp3911* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 struct iio_dev* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int mcp3911_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct mcp3911 *adc = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	clk_disable_unprepare(adc->clki);
	if (adc->vref)
		regulator_disable(adc->vref);

	return 0;
}