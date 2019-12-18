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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX5487_COPY_AB_TO_NV ; 
 struct iio_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 int max5487_write_cmd (struct spi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max5487_spi_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = dev_get_drvdata(&spi->dev);

	iio_device_unregister(indio_dev);

	/* save both wiper regs to NV regs */
	return max5487_write_cmd(spi, MAX5487_COPY_AB_TO_NV);
}