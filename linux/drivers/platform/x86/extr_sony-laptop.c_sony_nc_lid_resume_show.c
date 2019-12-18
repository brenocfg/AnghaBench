#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int /*<<< orphan*/  attr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {unsigned int status; TYPE_1__* attrs; } ;
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 unsigned int LID_RESUME_MAX ; 
 unsigned int LID_RESUME_S5 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_2__* lid_ctl ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static ssize_t sony_nc_lid_resume_show(struct device *dev,
					struct device_attribute *attr,
					char *buffer)
{
	unsigned int pos = LID_RESUME_S5;

	while (pos < LID_RESUME_MAX) {
		if (&lid_ctl->attrs[pos].attr == &attr->attr)
			return snprintf(buffer, PAGE_SIZE, "%d\n",
					(lid_ctl->status >> pos) & 0x01);
		pos++;
	}
	return -EINVAL;
}