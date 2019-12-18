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
struct vnic_wq {int /*<<< orphan*/  index; TYPE_1__* ctrl; struct vnic_dev* vdev; } ;
struct vnic_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  running; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vdev_neterr (struct vnic_dev*,char*,int /*<<< orphan*/ ) ; 

int vnic_wq_disable(struct vnic_wq *wq)
{
	unsigned int wait;
	struct vnic_dev *vdev = wq->vdev;

	iowrite32(0, &wq->ctrl->enable);

	/* Wait for HW to ACK disable request */
	for (wait = 0; wait < 1000; wait++) {
		if (!(ioread32(&wq->ctrl->running)))
			return 0;
		udelay(10);
	}

	vdev_neterr(vdev, "Failed to disable WQ[%d]\n", wq->index);

	return -ETIMEDOUT;
}