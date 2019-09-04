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
struct asic3_led {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 struct asic3_led* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ ) ; 
 int mfd_cell_disable (struct platform_device*) ; 

__attribute__((used)) static int asic3_led_remove(struct platform_device *pdev)
{
	struct asic3_led *led = dev_get_platdata(&pdev->dev);

	led_classdev_unregister(led->cdev);

	return mfd_cell_disable(pdev);
}