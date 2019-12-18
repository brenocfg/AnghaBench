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
struct oneshot_trig_data {int dummy; } ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  kfree (struct oneshot_trig_data*) ; 
 struct oneshot_trig_data* led_get_trigger_data (struct led_classdev*) ; 
 int /*<<< orphan*/  led_set_brightness (struct led_classdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void oneshot_trig_deactivate(struct led_classdev *led_cdev)
{
	struct oneshot_trig_data *oneshot_data = led_get_trigger_data(led_cdev);

	kfree(oneshot_data);

	/* Stop blinking */
	led_set_brightness(led_cdev, LED_OFF);
}