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
struct ccw_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int (* set ) (struct ccw_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* free ) (struct ccw_device*) ;int /*<<< orphan*/  attr_group; } ;

/* Variables and functions */
 TYPE_2__* cmbops ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int stub1 (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ccw_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int __disable_cmf(struct ccw_device *cdev)
{
	int ret;

	ret = cmbops->set(cdev, 0);
	if (ret)
		return ret;

	sysfs_remove_group(&cdev->dev.kobj, cmbops->attr_group);
	cmbops->free(cdev);
	put_device(&cdev->dev);

	return ret;
}