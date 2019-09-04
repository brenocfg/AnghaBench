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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bl_trig_notifier {int invert; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct bl_trig_notifier* led_trigger_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t bl_trig_invert_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct bl_trig_notifier *n = led_trigger_get_drvdata(dev);

	return sprintf(buf, "%u\n", n->invert);
}