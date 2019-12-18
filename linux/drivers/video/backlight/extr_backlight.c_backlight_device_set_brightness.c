#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long max_brightness; unsigned long brightness; } ;
struct backlight_device {int /*<<< orphan*/  ops_lock; TYPE_1__ props; scalar_t__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_UPDATE_SYSFS ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  backlight_generate_event (struct backlight_device*,int /*<<< orphan*/ ) ; 
 int backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 

int backlight_device_set_brightness(struct backlight_device *bd,
				    unsigned long brightness)
{
	int rc = -ENXIO;

	mutex_lock(&bd->ops_lock);
	if (bd->ops) {
		if (brightness > bd->props.max_brightness)
			rc = -EINVAL;
		else {
			pr_debug("set brightness to %lu\n", brightness);
			bd->props.brightness = brightness;
			rc = backlight_update_status(bd);
		}
	}
	mutex_unlock(&bd->ops_lock);

	backlight_generate_event(bd, BACKLIGHT_UPDATE_SYSFS);

	return rc;
}