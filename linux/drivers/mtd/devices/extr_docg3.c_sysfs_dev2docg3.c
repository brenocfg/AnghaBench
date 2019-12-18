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
struct mtd_info {struct docg3* priv; } ;
struct docg3 {int dummy; } ;
struct TYPE_2__ {int* name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DOC_MAX_NBFLOORS ; 
 struct mtd_info** dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct docg3 *sysfs_dev2docg3(struct device *dev,
				     struct device_attribute *attr)
{
	int floor;
	struct mtd_info **docg3_floors = dev_get_drvdata(dev);

	floor = attr->attr.name[1] - '0';
	if (floor < 0 || floor >= DOC_MAX_NBFLOORS)
		return NULL;
	else
		return docg3_floors[floor]->priv;
}