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
struct ktd2692_context {int /*<<< orphan*/  lock; scalar_t__ regulator; int /*<<< orphan*/  fled_cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  led_classdev_flash_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct ktd2692_context* platform_get_drvdata (struct platform_device*) ; 
 int regulator_disable (scalar_t__) ; 

__attribute__((used)) static int ktd2692_remove(struct platform_device *pdev)
{
	struct ktd2692_context *led = platform_get_drvdata(pdev);
	int ret;

	led_classdev_flash_unregister(&led->fled_cdev);

	if (led->regulator) {
		ret = regulator_disable(led->regulator);
		if (ret)
			dev_err(&pdev->dev,
				"Failed to disable supply: %d\n", ret);
	}

	mutex_destroy(&led->lock);

	return 0;
}