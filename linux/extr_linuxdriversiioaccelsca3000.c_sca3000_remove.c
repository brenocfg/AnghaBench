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
struct spi_device {scalar_t__ irq; } ;
struct sca3000_state {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sca3000_stop_all_interrupts (struct sca3000_state*) ; 
 struct iio_dev* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int sca3000_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct sca3000_state *st = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	/* Must ensure no interrupts can be generated after this! */
	sca3000_stop_all_interrupts(st);
	if (spi->irq)
		free_irq(spi->irq, indio_dev);

	return 0;
}