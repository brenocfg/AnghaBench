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
struct spi_driver {scalar_t__ id_table; } ;
struct spi_device {scalar_t__ modalias; scalar_t__ driver_override; } ;
struct device_driver {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_driver_match_device (struct device*,struct device_driver*) ; 
 scalar_t__ of_driver_match_device (struct device*,struct device_driver*) ; 
 int /*<<< orphan*/  spi_match_id (scalar_t__,struct spi_device const*) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (struct device*) ; 
 struct spi_driver* to_spi_driver (struct device_driver*) ; 

__attribute__((used)) static int spi_match_device(struct device *dev, struct device_driver *drv)
{
	const struct spi_device	*spi = to_spi_device(dev);
	const struct spi_driver	*sdrv = to_spi_driver(drv);

	/* Check override first, and if set, only use the named driver */
	if (spi->driver_override)
		return strcmp(spi->driver_override, drv->name) == 0;

	/* Attempt an OF style match */
	if (of_driver_match_device(dev, drv))
		return 1;

	/* Then try ACPI */
	if (acpi_driver_match_device(dev, drv))
		return 1;

	if (sdrv->id_table)
		return !!spi_match_id(sdrv->id_table, spi);

	return strcmp(spi->modalias, drv->name) == 0;
}