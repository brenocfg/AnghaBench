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
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct ca8210_platform_data* platform_data; } ;
struct spi_device {TYPE_1__ dev; } ;
struct ca8210_platform_data {int /*<<< orphan*/  gpio_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_crit (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca8210_reset_init(struct spi_device *spi)
{
	int ret;
	struct ca8210_platform_data *pdata = spi->dev.platform_data;

	pdata->gpio_reset = of_get_named_gpio(
		spi->dev.of_node,
		"reset-gpio",
		0
	);

	ret = gpio_direction_output(pdata->gpio_reset, 1);
	if (ret < 0) {
		dev_crit(
			&spi->dev,
			"Reset GPIO %d did not set to output mode\n",
			pdata->gpio_reset
		);
	}

	return ret;
}