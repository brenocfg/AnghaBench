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
struct transient_trig_data {int /*<<< orphan*/  restore_state; int /*<<< orphan*/  timer; } ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct transient_trig_data*) ; 
 struct transient_trig_data* led_get_trigger_data (struct led_classdev*) ; 
 int /*<<< orphan*/  led_set_brightness_nosleep (struct led_classdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void transient_trig_deactivate(struct led_classdev *led_cdev)
{
	struct transient_trig_data *transient_data = led_get_trigger_data(led_cdev);

	del_timer_sync(&transient_data->timer);
	led_set_brightness_nosleep(led_cdev, transient_data->restore_state);
	kfree(transient_data);
}