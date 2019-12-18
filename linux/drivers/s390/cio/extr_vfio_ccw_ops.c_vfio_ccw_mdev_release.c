#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfio_ccw_private {scalar_t__ state; int num_regions; TYPE_2__* region; int /*<<< orphan*/  nb; int /*<<< orphan*/  cp; } ;
struct mdev_device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* release ) (struct vfio_ccw_private*,TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ VFIO_CCW_STATE_NOT_OPER ; 
 scalar_t__ VFIO_CCW_STATE_STANDBY ; 
 int /*<<< orphan*/  VFIO_IOMMU_NOTIFY ; 
 int /*<<< orphan*/  cp_free (int /*<<< orphan*/ *) ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  mdev_dev (struct mdev_device*) ; 
 int /*<<< orphan*/  mdev_parent_dev (struct mdev_device*) ; 
 int /*<<< orphan*/  stub1 (struct vfio_ccw_private*,TYPE_2__*) ; 
 int /*<<< orphan*/  vfio_ccw_mdev_reset (struct mdev_device*) ; 
 int /*<<< orphan*/  vfio_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vfio_ccw_mdev_release(struct mdev_device *mdev)
{
	struct vfio_ccw_private *private =
		dev_get_drvdata(mdev_parent_dev(mdev));
	int i;

	if ((private->state != VFIO_CCW_STATE_NOT_OPER) &&
	    (private->state != VFIO_CCW_STATE_STANDBY)) {
		if (!vfio_ccw_mdev_reset(mdev))
			private->state = VFIO_CCW_STATE_STANDBY;
		/* The state will be NOT_OPER on error. */
	}

	cp_free(&private->cp);
	vfio_unregister_notifier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
				 &private->nb);

	for (i = 0; i < private->num_regions; i++)
		private->region[i].ops->release(private, &private->region[i]);

	private->num_regions = 0;
	kfree(private->region);
	private->region = NULL;
}