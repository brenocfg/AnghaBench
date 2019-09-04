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
struct led_classdev {int /*<<< orphan*/  work_flags; } ;
struct activity_data {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_SW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct activity_data*) ; 
 struct activity_data* led_get_trigger_data (struct led_classdev*) ; 

__attribute__((used)) static void activity_deactivate(struct led_classdev *led_cdev)
{
	struct activity_data *activity_data = led_get_trigger_data(led_cdev);

	del_timer_sync(&activity_data->timer);
	kfree(activity_data);
	clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
}