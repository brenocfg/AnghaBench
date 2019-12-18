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
struct rtc_device {int max_user_freq; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct rtc_device* to_rtc_device (struct device*) ; 

__attribute__((used)) static ssize_t
max_user_freq_store(struct device *dev, struct device_attribute *attr,
		    const char *buf, size_t n)
{
	struct rtc_device *rtc = to_rtc_device(dev);
	unsigned long val;
	int err;

	err = kstrtoul(buf, 0, &val);
	if (err)
		return err;

	if (val >= 4096 || val == 0)
		return -EINVAL;

	rtc->max_user_freq = (int)val;

	return n;
}