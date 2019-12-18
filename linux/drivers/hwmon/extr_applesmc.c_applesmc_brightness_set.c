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
struct led_classdev {int /*<<< orphan*/  dev; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  applesmc_led_wq ; 
 int* backlight_state ; 
 int /*<<< orphan*/  backlight_work ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void applesmc_brightness_set(struct led_classdev *led_cdev,
						enum led_brightness value)
{
	int ret;

	backlight_state[0] = value;
	ret = queue_work(applesmc_led_wq, &backlight_work);

	if (debug && (!ret))
		dev_dbg(led_cdev->dev, "work was already on the queue.\n");
}