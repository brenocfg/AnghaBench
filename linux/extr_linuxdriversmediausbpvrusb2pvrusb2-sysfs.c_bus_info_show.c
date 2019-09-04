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
struct TYPE_2__ {int /*<<< orphan*/  hdw; } ;
struct pvr2_sysfs {TYPE_1__ channel; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct pvr2_sysfs* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pvr2_hdw_get_bus_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t bus_info_show(struct device *class_dev,
			     struct device_attribute *attr, char *buf)
{
	struct pvr2_sysfs *sfp;
	sfp = dev_get_drvdata(class_dev);
	if (!sfp) return -EINVAL;
	return scnprintf(buf,PAGE_SIZE,"%s\n",
			 pvr2_hdw_get_bus_info(sfp->channel.hdw));
}