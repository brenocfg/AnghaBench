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
struct hts221_avg {int /*<<< orphan*/ * avg_avl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 size_t HTS221_SENSOR_H ; 
 scalar_t__ PAGE_SIZE ; 
 struct hts221_avg* hts221_avg_list ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
hts221_sysfs_rh_oversampling_avail(struct device *dev,
				   struct device_attribute *attr,
				   char *buf)
{
	const struct hts221_avg *avg = &hts221_avg_list[HTS221_SENSOR_H];
	ssize_t len = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(avg->avg_avl); i++)
		len += scnprintf(buf + len, PAGE_SIZE - len, "%d ",
				 avg->avg_avl[i]);
	buf[len - 1] = '\n';

	return len;
}