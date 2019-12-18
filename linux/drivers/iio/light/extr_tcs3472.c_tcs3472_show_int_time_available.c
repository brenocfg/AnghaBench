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
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int) ; 

__attribute__((used)) static ssize_t tcs3472_show_int_time_available(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	size_t len = 0;
	int i;

	for (i = 1; i <= 256; i++)
		len += scnprintf(buf + len, PAGE_SIZE - len, "0.%06d ",
			2400 * i);

	/* replace trailing space by newline */
	buf[len - 1] = '\n';

	return len;
}