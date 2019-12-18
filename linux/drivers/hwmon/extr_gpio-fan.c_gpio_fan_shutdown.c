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
struct gpio_fan_data {scalar_t__ gpios; } ;

/* Variables and functions */
 struct gpio_fan_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  set_fan_speed (struct gpio_fan_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_fan_shutdown(struct platform_device *pdev)
{
	struct gpio_fan_data *fan_data = platform_get_drvdata(pdev);

	if (fan_data->gpios)
		set_fan_speed(fan_data, 0);
}