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
struct led_classdev {void* blink_delay_off; void* blink_delay_on; } ;

/* Variables and functions */
 void* DEFAULT_DELAY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct oneshot_trig_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_set_trigger_data (struct led_classdev*,struct oneshot_trig_data*) ; 

__attribute__((used)) static int oneshot_trig_activate(struct led_classdev *led_cdev)
{
	struct oneshot_trig_data *oneshot_data;

	oneshot_data = kzalloc(sizeof(*oneshot_data), GFP_KERNEL);
	if (!oneshot_data)
		return -ENOMEM;

	led_set_trigger_data(led_cdev, oneshot_data);

	led_cdev->blink_delay_on = DEFAULT_DELAY;
	led_cdev->blink_delay_off = DEFAULT_DELAY;

	return 0;
}