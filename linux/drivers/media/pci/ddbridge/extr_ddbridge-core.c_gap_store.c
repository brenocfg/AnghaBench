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
struct TYPE_3__ {int* name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
struct ddb {TYPE_2__* port; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {unsigned int gap; } ;

/* Variables and functions */
 size_t EINVAL ; 
 struct ddb* dev_get_drvdata (struct device*) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static ssize_t gap_store(struct device *device, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct ddb *dev = dev_get_drvdata(device);
	int num = attr->attr.name[3] - 0x30;
	unsigned int val;

	if (sscanf(buf, "%u\n", &val) != 1)
		return -EINVAL;
	if (val > 128)
		return -EINVAL;
	if (val == 128)
		val = 0xffffffff;
	dev->port[num].gap = val;
	return count;
}