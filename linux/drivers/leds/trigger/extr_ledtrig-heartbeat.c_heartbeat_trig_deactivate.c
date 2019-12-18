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
struct heartbeat_trig_data {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_SW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct heartbeat_trig_data*) ; 
 struct heartbeat_trig_data* led_get_trigger_data (struct led_classdev*) ; 

__attribute__((used)) static void heartbeat_trig_deactivate(struct led_classdev *led_cdev)
{
	struct heartbeat_trig_data *heartbeat_data =
		led_get_trigger_data(led_cdev);

	del_timer_sync(&heartbeat_data->timer);
	kfree(heartbeat_data);
	clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
}