#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usnic_ib_dev {int /*<<< orphan*/  qpn_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 

void usnic_ib_sysfs_unregister_usdev(struct usnic_ib_dev *us_ibdev)
{
	kobject_put(us_ibdev->qpn_kobj);
}