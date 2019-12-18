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
struct vnic_rq {int /*<<< orphan*/  index; TYPE_1__* ctrl; struct vnic_dev* vdev; } ;
struct vnic_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  running; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_neterr (struct vnic_dev*,char*,int /*<<< orphan*/ ) ; 

int vnic_rq_disable(struct vnic_rq *rq)
{
	unsigned int wait;
	struct vnic_dev *vdev = rq->vdev;
	int i;

	/* Due to a race condition with clearing RQ "mini-cache" in hw, we need
	 * to disable the RQ twice to guarantee that stale descriptors are not
	 * used when this RQ is re-enabled.
	 */
	for (i = 0; i < 2; i++) {
		iowrite32(0, &rq->ctrl->enable);

		/* Wait for HW to ACK disable request */
		for (wait = 20000; wait > 0; wait--)
			if (!ioread32(&rq->ctrl->running))
				break;
		if (!wait) {
			vdev_neterr(vdev, "Failed to disable RQ[%d]\n",
				    rq->index);

			return -ETIMEDOUT;
		}
	}

	return 0;
}