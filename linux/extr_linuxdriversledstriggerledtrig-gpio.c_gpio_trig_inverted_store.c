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
struct gpio_trig_data {unsigned long inverted; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gpio_trig_irq (int /*<<< orphan*/ ,struct led_classdev*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 struct gpio_trig_data* led_trigger_get_drvdata (struct device*) ; 
 struct led_classdev* led_trigger_get_led (struct device*) ; 

__attribute__((used)) static ssize_t gpio_trig_inverted_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t n)
{
	struct led_classdev *led = led_trigger_get_led(dev);
	struct gpio_trig_data *gpio_data = led_trigger_get_drvdata(dev);
	unsigned long inverted;
	int ret;

	ret = kstrtoul(buf, 10, &inverted);
	if (ret < 0)
		return ret;

	if (inverted > 1)
		return -EINVAL;

	gpio_data->inverted = inverted;

	/* After inverting, we need to update the LED. */
	gpio_trig_irq(0, led);

	return n;
}