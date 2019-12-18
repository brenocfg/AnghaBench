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
typedef  int ssize_t ;
struct TYPE_2__ {int* cap; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int PAGE_SIZE ; 
 TYPE_1__* handles ; 
 int snprintf (char*,int,char*,...) ; 

__attribute__((used)) static ssize_t sony_nc_handles_show(struct device *dev,
		struct device_attribute *attr, char *buffer)
{
	ssize_t len = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(handles->cap); i++) {
		len += snprintf(buffer + len, PAGE_SIZE - len, "0x%.4x ",
				handles->cap[i]);
	}
	len += snprintf(buffer + len, PAGE_SIZE - len, "\n");

	return len;
}