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
struct ad_dpot_bus_data {int /*<<< orphan*/ * bops; struct spi_device* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int ad_dpot_probe (int /*<<< orphan*/ *,struct ad_dpot_bus_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bops ; 
 TYPE_1__* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int ad_dpot_spi_probe(struct spi_device *spi)
{
	struct ad_dpot_bus_data bdata = {
		.client = spi,
		.bops = &bops,
	};

	return ad_dpot_probe(&spi->dev, &bdata,
			     spi_get_device_id(spi)->driver_data,
			     spi_get_device_id(spi)->name);
}