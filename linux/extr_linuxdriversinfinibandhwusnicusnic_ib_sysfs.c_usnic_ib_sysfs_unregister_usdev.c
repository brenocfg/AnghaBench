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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct usnic_ib_dev {int /*<<< orphan*/  qpn_kobj; TYPE_1__ ib_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * usnic_class_attributes ; 

void usnic_ib_sysfs_unregister_usdev(struct usnic_ib_dev *us_ibdev)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(usnic_class_attributes); ++i) {
		device_remove_file(&us_ibdev->ib_dev.dev,
					usnic_class_attributes[i]);
	}

	kobject_put(us_ibdev->qpn_kobj);
}