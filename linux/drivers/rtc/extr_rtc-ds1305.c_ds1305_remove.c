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
struct spi_device {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct ds1305 {int /*<<< orphan*/  work; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_EXITING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,scalar_t__,struct ds1305*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ds1305* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int ds1305_remove(struct spi_device *spi)
{
	struct ds1305 *ds1305 = spi_get_drvdata(spi);

	/* carefully shut down irq and workqueue, if present */
	if (spi->irq) {
		set_bit(FLAG_EXITING, &ds1305->flags);
		devm_free_irq(&spi->dev, spi->irq, ds1305);
		cancel_work_sync(&ds1305->work);
	}

	return 0;
}