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
struct aat1290_led {int /*<<< orphan*/  lock; int /*<<< orphan*/  fled_cdev; int /*<<< orphan*/  v4l2_flash; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_flash_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct aat1290_led* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_flash_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aat1290_led_remove(struct platform_device *pdev)
{
	struct aat1290_led *led = platform_get_drvdata(pdev);

	v4l2_flash_release(led->v4l2_flash);
	led_classdev_flash_unregister(&led->fled_cdev);

	mutex_destroy(&led->lock);

	return 0;
}