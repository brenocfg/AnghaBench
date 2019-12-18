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
struct led_classdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  led_access; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_SYSFS_DISABLE ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void led_sysfs_disable(struct led_classdev *led_cdev)
{
	lockdep_assert_held(&led_cdev->led_access);

	led_cdev->flags |= LED_SYSFS_DISABLE;
}