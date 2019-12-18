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
struct max5481_data {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX5481_COPY_AB_TO_NV ; 
 struct iio_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct max5481_data* iio_priv (struct iio_dev*) ; 
 int max5481_write_cmd (struct max5481_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max5481_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = dev_get_drvdata(&spi->dev);
	struct max5481_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	/* save wiper reg to NV reg */
	return max5481_write_cmd(data, MAX5481_COPY_AB_TO_NV, 0);
}