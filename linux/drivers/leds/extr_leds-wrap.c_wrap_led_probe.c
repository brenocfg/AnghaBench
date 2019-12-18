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

/* Variables and functions */
 int devm_led_classdev_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrap_error_led ; 
 int /*<<< orphan*/  wrap_extra_led ; 
 int /*<<< orphan*/  wrap_power_led ; 

__attribute__((used)) static int wrap_led_probe(struct platform_device *pdev)
{
	int ret;

	ret = devm_led_classdev_register(&pdev->dev, &wrap_power_led);
	if (ret < 0)
		return ret;

	ret = devm_led_classdev_register(&pdev->dev, &wrap_error_led);
	if (ret < 0)
		return ret;

	return  devm_led_classdev_register(&pdev->dev, &wrap_extra_led);
}