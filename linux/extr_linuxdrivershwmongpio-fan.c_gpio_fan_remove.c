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
struct platform_device {int dummy; } ;
struct gpio_fan_data {scalar_t__ gpios; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 struct gpio_fan_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  set_fan_speed (struct gpio_fan_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_fan_remove(struct platform_device *pdev)
{
	struct gpio_fan_data *fan_data = platform_get_drvdata(pdev);

	if (!IS_ERR(fan_data->cdev))
		thermal_cooling_device_unregister(fan_data->cdev);

	if (fan_data->gpios)
		set_fan_speed(fan_data, 0);

	return 0;
}