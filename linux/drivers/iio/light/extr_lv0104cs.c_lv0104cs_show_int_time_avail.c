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
struct TYPE_3__ {int /*<<< orphan*/  val2; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_1__* lv0104cs_int_times ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t lv0104cs_show_int_time_avail(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	ssize_t len = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(lv0104cs_int_times); i++) {
		len += scnprintf(buf + len, PAGE_SIZE - len, "%d.%06d ",
				lv0104cs_int_times[i].val,
				lv0104cs_int_times[i].val2);
	}

	buf[len - 1] = '\n';

	return len;
}