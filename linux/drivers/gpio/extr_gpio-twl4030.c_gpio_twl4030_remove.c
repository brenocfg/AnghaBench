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
struct twl4030_gpio_platform_data {int (* teardown ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct gpio_twl4030_priv {TYPE_1__ gpio_chip; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TWL4030_GPIO_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct twl4030_gpio_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_1__*) ; 
 scalar_t__ is_module () ; 
 struct gpio_twl4030_priv* platform_get_drvdata (struct platform_device*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_twl4030_remove(struct platform_device *pdev)
{
	struct twl4030_gpio_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct gpio_twl4030_priv *priv = platform_get_drvdata(pdev);
	int status;

	if (pdata && pdata->teardown) {
		status = pdata->teardown(&pdev->dev, priv->gpio_chip.base,
					 TWL4030_GPIO_MAX);
		if (status) {
			dev_dbg(&pdev->dev, "teardown --> %d\n", status);
			return status;
		}
	}

	gpiochip_remove(&priv->gpio_chip);

	if (is_module())
		return 0;

	/* REVISIT no support yet for deregistering all the IRQs */
	WARN_ON(1);
	return -EIO;
}