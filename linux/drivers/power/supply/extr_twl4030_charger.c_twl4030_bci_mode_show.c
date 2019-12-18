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
struct twl4030_bci {int usb_mode; int ac_mode; TYPE_1__* ac; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 scalar_t__ PAGE_SIZE ; 
 struct twl4030_bci* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 char** modes ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,char*) ; 

__attribute__((used)) static ssize_t
twl4030_bci_mode_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct twl4030_bci *bci = dev_get_drvdata(dev->parent);
	int len = 0;
	int i;
	int mode = bci->usb_mode;

	if (dev == &bci->ac->dev)
		mode = bci->ac_mode;

	for (i = 0; i < ARRAY_SIZE(modes); i++)
		if (mode == i)
			len += snprintf(buf+len, PAGE_SIZE-len,
					"[%s] ", modes[i]);
		else
			len += snprintf(buf+len, PAGE_SIZE-len,
					"%s ", modes[i]);
	buf[len-1] = '\n';
	return len;
}