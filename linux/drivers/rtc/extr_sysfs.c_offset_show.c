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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ rtc_read_offset (int /*<<< orphan*/ ,long*) ; 
 scalar_t__ sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  to_rtc_device (struct device*) ; 

__attribute__((used)) static ssize_t
offset_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	ssize_t retval;
	long offset;

	retval = rtc_read_offset(to_rtc_device(dev), &offset);
	if (retval == 0)
		retval = sprintf(buf, "%ld\n", offset);

	return retval;
}