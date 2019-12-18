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
struct spi_device {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct ds1343_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  irqen; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_AF ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,scalar_t__,struct ds1343_priv*) ; 
 int /*<<< orphan*/  ds1343_sysfs_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ds1343_priv* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1343_remove(struct spi_device *spi)
{
	struct ds1343_priv *priv = spi_get_drvdata(spi);

	if (spi->irq) {
		mutex_lock(&priv->mutex);
		priv->irqen &= ~RTC_AF;
		mutex_unlock(&priv->mutex);

		dev_pm_clear_wake_irq(&spi->dev);
		device_init_wakeup(&spi->dev, false);
		devm_free_irq(&spi->dev, spi->irq, priv);
	}

	spi_set_drvdata(spi, NULL);

	ds1343_sysfs_unregister(&spi->dev);

	return 0;
}