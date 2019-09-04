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
struct bd2802_led {int /*<<< orphan*/  cdev_led1r; int /*<<< orphan*/  cdev_led1g; int /*<<< orphan*/  cdev_led1b; int /*<<< orphan*/  cdev_led2r; int /*<<< orphan*/  cdev_led2g; int /*<<< orphan*/  cdev_led2b; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bd2802_unregister_led_classdev(struct bd2802_led *led)
{
	led_classdev_unregister(&led->cdev_led2b);
	led_classdev_unregister(&led->cdev_led2g);
	led_classdev_unregister(&led->cdev_led2r);
	led_classdev_unregister(&led->cdev_led1b);
	led_classdev_unregister(&led->cdev_led1g);
	led_classdev_unregister(&led->cdev_led1r);
}