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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RTC_HCTOSYS_DEVICE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ rtc_hctosys_ret ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_rtc_device (struct device*) ; 

__attribute__((used)) static ssize_t
hctosys_show(struct device *dev, struct device_attribute *attr, char *buf)
{
#ifdef CONFIG_RTC_HCTOSYS_DEVICE
	if (rtc_hctosys_ret == 0 &&
	    strcmp(dev_name(&to_rtc_device(dev)->dev),
		   CONFIG_RTC_HCTOSYS_DEVICE) == 0)
		return sprintf(buf, "1\n");
#endif
	return sprintf(buf, "0\n");
}