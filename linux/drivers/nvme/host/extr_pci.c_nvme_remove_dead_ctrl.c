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
struct nvme_dev {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  remove_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_CTRL_DELETING ; 
 int /*<<< orphan*/  nvme_change_ctrl_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_dev_disable (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  nvme_get_ctrl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_kill_queues (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_put_ctrl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_remove_dead_ctrl(struct nvme_dev *dev)
{
	/*
	 * Set state to deleting now to avoid blocking nvme_wait_reset(), which
	 * may be holding this pci_dev's device lock.
	 */
	nvme_change_ctrl_state(&dev->ctrl, NVME_CTRL_DELETING);
	nvme_get_ctrl(&dev->ctrl);
	nvme_dev_disable(dev, false);
	nvme_kill_queues(&dev->ctrl);
	if (!queue_work(nvme_wq, &dev->remove_work))
		nvme_put_ctrl(&dev->ctrl);
}