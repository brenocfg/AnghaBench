#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  hz; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_1__* hts221_odr_table ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t hts221_sysfs_sampling_freq(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	int i;
	ssize_t len = 0;

	for (i = 0; i < ARRAY_SIZE(hts221_odr_table); i++)
		len += scnprintf(buf + len, PAGE_SIZE - len, "%d ",
				 hts221_odr_table[i].hz);
	buf[len - 1] = '\n';

	return len;
}