#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct panel_drv_data {int res_gpio; int /*<<< orphan*/  qvga_gpio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct panel_drv_data* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nec_8048_probe_of(struct spi_device *spi)
{
	struct device_node *node = spi->dev.of_node;
	struct panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	int gpio;

	gpio = of_get_named_gpio(node, "reset-gpios", 0);
	if (!gpio_is_valid(gpio)) {
		dev_err(&spi->dev, "failed to parse enable gpio\n");
		return gpio;
	}
	ddata->res_gpio = gpio;

	/* XXX the panel spec doesn't mention any QVGA pin?? */
	ddata->qvga_gpio = -ENOENT;

	return 0;
}