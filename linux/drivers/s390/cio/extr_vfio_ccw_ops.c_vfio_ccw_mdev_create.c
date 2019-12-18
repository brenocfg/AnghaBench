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
struct vfio_ccw_private {scalar_t__ state; TYPE_2__* sch; struct mdev_device* mdev; int /*<<< orphan*/  avail; } ;
struct mdev_device {int dummy; } ;
struct kobject {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; int /*<<< orphan*/  cssid; } ;
struct TYPE_4__ {TYPE_1__ schid; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  VFIO_CCW_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VFIO_CCW_STATE_IDLE ; 
 scalar_t__ VFIO_CCW_STATE_NOT_OPER ; 
 scalar_t__ atomic_dec_if_positive (int /*<<< orphan*/ *) ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdev_parent_dev (struct mdev_device*) ; 
 int /*<<< orphan*/  mdev_uuid (struct mdev_device*) ; 

__attribute__((used)) static int vfio_ccw_mdev_create(struct kobject *kobj, struct mdev_device *mdev)
{
	struct vfio_ccw_private *private =
		dev_get_drvdata(mdev_parent_dev(mdev));

	if (private->state == VFIO_CCW_STATE_NOT_OPER)
		return -ENODEV;

	if (atomic_dec_if_positive(&private->avail) < 0)
		return -EPERM;

	private->mdev = mdev;
	private->state = VFIO_CCW_STATE_IDLE;

	VFIO_CCW_MSG_EVENT(2, "mdev %pUl, sch %x.%x.%04x: create\n",
			   mdev_uuid(mdev), private->sch->schid.cssid,
			   private->sch->schid.ssid,
			   private->sch->schid.sch_no);

	return 0;
}