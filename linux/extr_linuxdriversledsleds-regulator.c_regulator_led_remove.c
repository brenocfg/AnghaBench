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
struct regulator_led {int /*<<< orphan*/  cdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 struct regulator_led* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_led_disable (struct regulator_led*) ; 

__attribute__((used)) static int regulator_led_remove(struct platform_device *pdev)
{
	struct regulator_led *led = platform_get_drvdata(pdev);

	led_classdev_unregister(&led->cdev);
	regulator_led_disable(led);
	return 0;
}