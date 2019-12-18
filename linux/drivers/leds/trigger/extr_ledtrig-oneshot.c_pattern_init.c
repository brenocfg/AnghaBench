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
typedef  void* u32 ;
struct led_classdev {void* blink_delay_off; void* blink_delay_on; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* DEFAULT_DELAY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void** led_get_default_pattern (struct led_classdev*,unsigned int*) ; 

__attribute__((used)) static void pattern_init(struct led_classdev *led_cdev)
{
	u32 *pattern;
	unsigned int size = 0;

	pattern = led_get_default_pattern(led_cdev, &size);
	if (!pattern)
		goto out_default;

	if (size != 2) {
		dev_warn(led_cdev->dev,
			 "Expected 2 but got %u values for delays pattern\n",
			 size);
		goto out_default;
	}

	led_cdev->blink_delay_on = pattern[0];
	led_cdev->blink_delay_off = pattern[1];
	kfree(pattern);

	return;

out_default:
	kfree(pattern);
	led_cdev->blink_delay_on = DEFAULT_DELAY;
	led_cdev->blink_delay_off = DEFAULT_DELAY;
}