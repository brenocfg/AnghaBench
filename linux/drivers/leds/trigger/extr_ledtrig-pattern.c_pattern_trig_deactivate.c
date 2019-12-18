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
struct pattern_trig_data {int /*<<< orphan*/  timer; } ;
struct led_classdev {int activated; int /*<<< orphan*/  (* pattern_clear ) (struct led_classdev*) ;struct pattern_trig_data* trigger_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pattern_trig_data*) ; 
 int /*<<< orphan*/  led_set_brightness (struct led_classdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct led_classdev*) ; 

__attribute__((used)) static void pattern_trig_deactivate(struct led_classdev *led_cdev)
{
	struct pattern_trig_data *data = led_cdev->trigger_data;

	if (!led_cdev->activated)
		return;

	if (led_cdev->pattern_clear)
		led_cdev->pattern_clear(led_cdev);

	del_timer_sync(&data->timer);

	led_set_brightness(led_cdev, LED_OFF);
	kfree(data);
	led_cdev->activated = false;
}