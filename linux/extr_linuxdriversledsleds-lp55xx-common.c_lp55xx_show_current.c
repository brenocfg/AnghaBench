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
struct lp55xx_led {int /*<<< orphan*/  led_current; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct lp55xx_led* dev_to_lp55xx_led (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t lp55xx_show_current(struct device *dev,
			    struct device_attribute *attr,
			    char *buf)
{
	struct lp55xx_led *led = dev_to_lp55xx_led(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", led->led_current);
}