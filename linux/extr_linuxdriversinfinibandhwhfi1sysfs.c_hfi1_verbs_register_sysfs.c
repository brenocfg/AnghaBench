#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;
struct ib_device {struct device dev; } ;
struct TYPE_9__ {struct ib_device ibdev; } ;
struct TYPE_10__ {TYPE_1__ rdi; } ;
struct hfi1_devdata {int num_sdma; TYPE_3__* per_sdma; TYPE_2__ verbs_dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  attr; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__**) ; 
 int device_create_file (struct device*,TYPE_4__*) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,TYPE_4__*) ; 
 TYPE_4__** hfi1_attributes ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 TYPE_4__** sde_attribs ; 
 int /*<<< orphan*/  sde_ktype ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int hfi1_verbs_register_sysfs(struct hfi1_devdata *dd)
{
	struct ib_device *dev = &dd->verbs_dev.rdi.ibdev;
	struct device *class_dev = &dev->dev;
	int i, j, ret;

	for (i = 0; i < ARRAY_SIZE(hfi1_attributes); ++i) {
		ret = device_create_file(&dev->dev, hfi1_attributes[i]);
		if (ret)
			goto bail;
	}

	for (i = 0; i < dd->num_sdma; i++) {
		ret = kobject_init_and_add(&dd->per_sdma[i].kobj,
					   &sde_ktype, &class_dev->kobj,
					   "sdma%d", i);
		if (ret)
			goto bail;

		for (j = 0; j < ARRAY_SIZE(sde_attribs); j++) {
			ret = sysfs_create_file(&dd->per_sdma[i].kobj,
						&sde_attribs[j]->attr);
			if (ret)
				goto bail;
		}
	}

	return 0;
bail:
	for (i = 0; i < ARRAY_SIZE(hfi1_attributes); ++i)
		device_remove_file(&dev->dev, hfi1_attributes[i]);

	for (i = 0; i < dd->num_sdma; i++)
		kobject_del(&dd->per_sdma[i].kobj);

	return ret;
}