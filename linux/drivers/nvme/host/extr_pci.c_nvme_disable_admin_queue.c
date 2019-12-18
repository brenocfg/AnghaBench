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
struct nvme_queue {int dummy; } ;
struct nvme_dev {int /*<<< orphan*/  ctrl; struct nvme_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_disable_ctrl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_poll_irqdisable (struct nvme_queue*,int) ; 
 int /*<<< orphan*/  nvme_shutdown_ctrl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_disable_admin_queue(struct nvme_dev *dev, bool shutdown)
{
	struct nvme_queue *nvmeq = &dev->queues[0];

	if (shutdown)
		nvme_shutdown_ctrl(&dev->ctrl);
	else
		nvme_disable_ctrl(&dev->ctrl);

	nvme_poll_irqdisable(nvmeq, -1);
}