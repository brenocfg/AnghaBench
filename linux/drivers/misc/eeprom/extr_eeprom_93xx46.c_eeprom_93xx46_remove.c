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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct eeprom_93xx46_dev {TYPE_1__* pdata; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EE_READONLY ; 
 int /*<<< orphan*/  dev_attr_erase ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct eeprom_93xx46_dev* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int eeprom_93xx46_remove(struct spi_device *spi)
{
	struct eeprom_93xx46_dev *edev = spi_get_drvdata(spi);

	if (!(edev->pdata->flags & EE_READONLY))
		device_remove_file(&spi->dev, &dev_attr_erase);

	return 0;
}