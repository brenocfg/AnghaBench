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
struct led_classdev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bl_trig_notifier {unsigned long invert; scalar_t__ old_status; int /*<<< orphan*/  brightness; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ BLANK ; 
 int EINVAL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  led_set_brightness_nosleep (struct led_classdev*,int /*<<< orphan*/ ) ; 
 struct bl_trig_notifier* led_trigger_get_drvdata (struct device*) ; 
 struct led_classdev* led_trigger_get_led (struct device*) ; 

__attribute__((used)) static ssize_t bl_trig_invert_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t num)
{
	struct led_classdev *led = led_trigger_get_led(dev);
	struct bl_trig_notifier *n = led_trigger_get_drvdata(dev);
	unsigned long invert;
	int ret;

	ret = kstrtoul(buf, 10, &invert);
	if (ret < 0)
		return ret;

	if (invert > 1)
		return -EINVAL;

	n->invert = invert;

	/* After inverting, we need to update the LED. */
	if ((n->old_status == BLANK) ^ n->invert)
		led_set_brightness_nosleep(led, LED_OFF);
	else
		led_set_brightness_nosleep(led, n->brightness);

	return num;
}