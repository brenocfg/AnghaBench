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
struct powernv_led_common {int led_disabled; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct powernv_led_common* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int powernv_led_remove(struct platform_device *pdev)
{
	struct powernv_led_common *powernv_led_common;

	/* Disable LED operation */
	powernv_led_common = platform_get_drvdata(pdev);
	powernv_led_common->led_disabled = true;

	/* Destroy lock */
	mutex_destroy(&powernv_led_common->lock);

	dev_info(&pdev->dev, "PowerNV led module unregistered\n");
	return 0;
}