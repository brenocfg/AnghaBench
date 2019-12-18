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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  micro_led ; 

__attribute__((used)) static int micro_leds_probe(struct platform_device *pdev)
{
	int ret;

	ret = devm_led_classdev_register(&pdev->dev, &micro_led);
	if (ret) {
		dev_err(&pdev->dev, "registering led failed: %d\n", ret);
		return ret;
	}
	dev_info(&pdev->dev, "iPAQ micro notification LED driver\n");

	return 0;
}