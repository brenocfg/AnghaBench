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
struct spi_device {int /*<<< orphan*/  chip_select; TYPE_1__* controller; int /*<<< orphan*/  dev; } ;
struct chip_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct chip_data*) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 

__attribute__((used)) static void dspi_cleanup(struct spi_device *spi)
{
	struct chip_data *chip = spi_get_ctldata((struct spi_device *)spi);

	dev_dbg(&spi->dev, "spi_device %u.%u cleanup\n",
		spi->controller->bus_num, spi->chip_select);

	kfree(chip);
}