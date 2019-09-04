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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct jz4740_mmc_platform_data {int /*<<< orphan*/  gpio_power; } ;

/* Variables and functions */
 struct jz4740_mmc_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jz4740_mmc_free_gpios(struct platform_device *pdev)
{
	struct jz4740_mmc_platform_data *pdata = dev_get_platdata(&pdev->dev);

	if (!pdata)
		return;

	if (gpio_is_valid(pdata->gpio_power))
		gpio_free(pdata->gpio_power);
}