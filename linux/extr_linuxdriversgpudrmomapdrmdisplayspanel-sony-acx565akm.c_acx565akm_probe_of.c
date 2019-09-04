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
struct TYPE_2__ {struct device_node* of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct panel_drv_data {int /*<<< orphan*/  reset_gpio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct panel_drv_data* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acx565akm_probe_of(struct spi_device *spi)
{
	struct panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	struct device_node *np = spi->dev.of_node;

	ddata->reset_gpio = of_get_named_gpio(np, "reset-gpios", 0);

	return 0;
}