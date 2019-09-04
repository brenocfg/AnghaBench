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
struct iio_dev {int dummy; } ;
struct afe4403_data {scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  regulator; int /*<<< orphan*/  trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct afe4403_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 struct iio_dev* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int afe4403_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct afe4403_data *afe = iio_priv(indio_dev);
	int ret;

	iio_device_unregister(indio_dev);

	iio_triggered_buffer_cleanup(indio_dev);

	if (afe->irq > 0)
		iio_trigger_unregister(afe->trig);

	ret = regulator_disable(afe->regulator);
	if (ret) {
		dev_err(afe->dev, "Unable to disable regulator\n");
		return ret;
	}

	return 0;
}