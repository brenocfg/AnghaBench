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
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct usnic_ib_dev {TYPE_2__ ib_dev; int /*<<< orphan*/ * qpn_kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

int usnic_ib_sysfs_register_usdev(struct usnic_ib_dev *us_ibdev)
{
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