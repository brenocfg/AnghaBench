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
struct led_classdev {int flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LED_INIT_DEFAULT_TRIGGER ; 
 struct oneshot_trig_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_set_trigger_data (struct led_classdev*,struct oneshot_trig_data*) ; 
 int /*<<< orphan*/  pattern_init (struct led_classdev*) ; 

__attribute__((used)) static int oneshot_trig_activate(struct led_classdev *led_cdev)
{
	struct oneshot_trig_data *oneshot_data;

	oneshot_data = kzalloc(sizeof(*oneshot_data), GFP_KERNEL);
	if (!oneshot_data)
		return -ENOMEM;

	led_set_trigger_data(led_cdev, oneshot_data);

	if (led_cdev->flags & LED_INIT_DEFAULT_TRIGGER) {
		pattern_init(led_cdev);
		/*
		 * Mark as initialized even on pattern_init() error because
		 * any consecutive call to it would produce the same error.
		 */
		led_cdev->flags &= ~LED_INIT_DEFAULT_TRIGGER;
	}

	return 0;
}