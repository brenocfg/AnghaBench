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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct usnic_ib_dev {TYPE_1__ ib_dev; int /*<<< orphan*/ * qpn_kobj; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int device_create_file (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * usnic_class_attributes ; 
 int /*<<< orphan*/  usnic_err (char*,int,int /*<<< orphan*/ ,int) ; 

int usnic_ib_sysfs_register_usdev(struct usnic_ib_dev *us_ibdev)
{
	int i;
	int err;
	for (i = 0; i < ARRAY_SIZE(usnic_class_attributes); ++i) {
		err = device_create_file(&us_ibdev->ib_dev.dev,
						usnic_class_attributes[i]);
		if (err) {
			usnic_err("Failed to create device file %d for %s eith err %d",
				i, us_ibdev->ib_dev.name, err);
			return -EINVAL;
		}
	}

	/* create kernel object for looking at individual QPs */
	kobject_get(&us_ibdev->ib_dev.dev.kobj);
	us_ibdev->qpn_kobj = kobject_create_and_add("qpn",
			&us_ibdev->ib_dev.dev.kobj);
	if (us_ibdev->qpn_kobj == NULL) {
		kobject_put(&us_ibdev->ib_dev.dev.kobj);
		return -ENOMEM;
	}

	return 0;
}