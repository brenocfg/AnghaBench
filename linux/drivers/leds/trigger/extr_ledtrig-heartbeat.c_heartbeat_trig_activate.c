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
struct led_classdev {int /*<<< orphan*/  work_flags; scalar_t__ max_brightness; scalar_t__ blink_brightness; } ;
struct heartbeat_trig_data {int /*<<< orphan*/  timer; scalar_t__ phase; struct led_classdev* led_cdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_BLINK_SW ; 
 struct heartbeat_trig_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_heartbeat_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_set_trigger_data (struct led_classdev*,struct heartbeat_trig_data*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ ) ; 

__attribute__((used)) static int heartbeat_trig_activate(struct led_classdev *led_cdev)
{
	struct heartbeat_trig_data *heartbeat_data;

	heartbeat_data = kzalloc(sizeof(*heartbeat_data), GFP_KERNEL);
	if (!heartbeat_data)
		return -ENOMEM;

	led_set_trigger_data(led_cdev, heartbeat_data);
	heartbeat_data->led_cdev = led_cdev;

	timer_setup(&heartbeat_data->timer, led_heartbeat_function, 0);
	heartbeat_data->phase = 0;
	if (!led_cdev->blink_brightness)
		led_cdev->blink_brightness = led_cdev->max_brightness;
	led_heartbeat_function(&heartbeat_data->timer);
	set_bit(LED_BLINK_SW, &led_cdev->work_flags);

	return 0;
}