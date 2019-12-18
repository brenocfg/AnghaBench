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
struct rtc_device {int /*<<< orphan*/  owner; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* class_find_device_by_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  rtc_class ; 
 struct rtc_device* to_rtc_device (struct device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct rtc_device *rtc_class_open(const char *name)
{
	struct device *dev;
	struct rtc_device *rtc = NULL;

	dev = class_find_device_by_name(rtc_class, name);
	if (dev)
		rtc = to_rtc_device(dev);

	if (rtc) {
		if (!try_module_get(rtc->owner)) {
			put_device(dev);
			rtc = NULL;
		}
	}

	return rtc;
}