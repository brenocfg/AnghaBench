#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__** attrs; } ;
struct fw_attribute_group {TYPE_2__** groups; TYPE_1__** attrs; TYPE_2__ group; } ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;
struct device_attribute {scalar_t__ (* show ) (struct device*,struct device_attribute*,int /*<<< orphan*/ *) ;TYPE_1__ attr; } ;
struct device {struct attribute_group const** groups; } ;
struct attribute_group {int dummy; } ;
struct TYPE_7__ {struct device_attribute attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 TYPE_3__* config_rom_attributes ; 
 scalar_t__ stub1 (struct device*,struct device_attribute*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_fw_attribute_group(struct device *dev,
				    struct device_attribute *attrs,
				    struct fw_attribute_group *group)
{
	struct device_attribute *attr;
	int i, j;

	for (j = 0; attrs[j].attr.name != NULL; j++)
		group->attrs[j] = &attrs[j].attr;

	for (i = 0; i < ARRAY_SIZE(config_rom_attributes); i++) {
		attr = &config_rom_attributes[i].attr;
		if (attr->show(dev, attr, NULL) < 0)
			continue;
		group->attrs[j++] = &attr->attr;
	}

	group->attrs[j] = NULL;
	group->groups[0] = &group->group;
	group->groups[1] = NULL;
	group->group.attrs = group->attrs;
	dev->groups = (const struct attribute_group **) group->groups;
}