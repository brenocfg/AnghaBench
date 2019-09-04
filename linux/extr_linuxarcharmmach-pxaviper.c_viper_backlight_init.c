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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIPER_BCKLIGHT_EN_GPIO ; 
 int /*<<< orphan*/  VIPER_LCD_EN_GPIO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int viper_backlight_init(struct device *dev)
{
	int ret;

	/* GPIO9 and 10 control FB backlight. Initialise to off */
	ret = gpio_request(VIPER_BCKLIGHT_EN_GPIO, "Backlight");
	if (ret)
		goto err_request_bckl;

	ret = gpio_request(VIPER_LCD_EN_GPIO, "LCD");
	if (ret)
		goto err_request_lcd;

	ret = gpio_direction_output(VIPER_BCKLIGHT_EN_GPIO, 0);
	if (ret)
		goto err_dir;

	ret = gpio_direction_output(VIPER_LCD_EN_GPIO, 0);
	if (ret)
		goto err_dir;

	return 0;

err_dir:
	gpio_free(VIPER_LCD_EN_GPIO);
err_request_lcd:
	gpio_free(VIPER_BCKLIGHT_EN_GPIO);
err_request_bckl:
	dev_err(dev, "Failed to setup LCD GPIOs\n");

	return ret;
}