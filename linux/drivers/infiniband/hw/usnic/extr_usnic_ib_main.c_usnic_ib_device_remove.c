#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct usnic_ib_dev {TYPE_1__ ib_dev; int /*<<< orphan*/  ufdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dealloc_device (TYPE_1__*) ; 
 int /*<<< orphan*/  ib_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  usnic_fwd_dev_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_ib_sysfs_unregister_usdev (struct usnic_ib_dev*) ; 
 int /*<<< orphan*/  usnic_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usnic_ib_device_remove(struct usnic_ib_dev *us_ibdev)
{
	usnic_info("Unregistering %s\n", dev_name(&us_ibdev->ib_dev.dev));
	usnic_ib_sysfs_unregister_usdev(us_ibdev);
	usnic_fwd_dev_free(us_ibdev->ufdev);
	ib_unregister_device(&us_ibdev->ib_dev);
	ib_dealloc_device(&us_ibdev->ib_dev);
}