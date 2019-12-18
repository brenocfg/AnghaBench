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
 int ARRAY_SIZE (int*) ; 
 int* als_it_value ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t cm32181_get_it_available(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	int i, n, len;

	n = ARRAY_SIZE(als_it_value);
	for (i = 0, len = 0; i < n; i++)
		len += sprintf(buf + len, "0.%06u ", als_it_value[i]);
	return len + sprintf(buf + len, "\n");
}