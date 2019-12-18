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
struct spi_device_id {int driver_data; int /*<<< orphan*/  name; } ;
struct spi_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct ad7606_bus_ops {int dummy; } ;

/* Variables and functions */
#define  ID_AD7606B 129 
#define  ID_AD7616 128 
 struct ad7606_bus_ops ad7606B_spi_bops ; 
 int ad7606_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct ad7606_bus_ops const*) ; 
 struct ad7606_bus_ops ad7606_spi_bops ; 
 struct ad7606_bus_ops ad7616_spi_bops ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int ad7606_spi_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);
	const struct ad7606_bus_ops *bops;

	switch (id->driver_data) {
	case ID_AD7616:
		bops = &ad7616_spi_bops;
		break;
	case ID_AD7606B:
		bops = &ad7606B_spi_bops;
		break;
	default:
		bops = &ad7606_spi_bops;
		break;
	}

	return ad7606_probe(&spi->dev, spi->irq, NULL,
			    id->name, id->driver_data,
			    bops);
}