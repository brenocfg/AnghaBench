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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPO_BLINK ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  nasgpio_led_set_attr (struct led_classdev*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static ssize_t nas_led_blink_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t size)
{
	int ret;
	struct led_classdev *led = dev_get_drvdata(dev);
	unsigned long blink_state;

	ret = kstrtoul(buf, 10, &blink_state);
	if (ret)
		return ret;

	nasgpio_led_set_attr(led, GPO_BLINK, blink_state);

	return size;
}