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
struct st_sensors_platform_data {scalar_t__ spi_3wire; } ;
struct TYPE_2__ {scalar_t__ platform_data; struct device_node* of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static bool st_sensors_is_spi_3_wire(struct spi_device *spi)
{
	struct device_node *np = spi->dev.of_node;
	struct st_sensors_platform_data *pdata;

	pdata = (struct st_sensors_platform_data *)spi->dev.platform_data;
	if ((np && of_property_read_bool(np, "spi-3wire")) ||
	    (pdata && pdata->spi_3wire)) {
		return true;
	}

	return false;
}