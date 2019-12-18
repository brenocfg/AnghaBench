#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {scalar_t__ error_state; } ;
struct TYPE_6__ {scalar_t__ state; scalar_t__ queue_count; scalar_t__ admin_q; } ;
struct nvme_dev {int /*<<< orphan*/  shutdown_lock; TYPE_1__ ctrl; int /*<<< orphan*/  admin_tagset; int /*<<< orphan*/  tagset; int /*<<< orphan*/ * queues; scalar_t__ bar; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NVME_CSTS_CFS ; 
 int NVME_CSTS_RDY ; 
 scalar_t__ NVME_CTRL_LIVE ; 
 scalar_t__ NVME_CTRL_RESETTING ; 
 int /*<<< orphan*/  NVME_IO_TIMEOUT ; 
 scalar_t__ NVME_REG_CSTS ; 
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  blk_mq_tagset_wait_completed_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_dying (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_cancel_request ; 
 int /*<<< orphan*/  nvme_disable_admin_queue (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  nvme_disable_io_queues (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_pci_disable (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_start_freeze (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_start_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_stop_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_suspend_io_queues (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_suspend_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_wait_freeze_timeout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_channel_io_normal ; 
 scalar_t__ pci_is_enabled (struct pci_dev*) ; 
 int readl (scalar_t__) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_dev_disable(struct nvme_dev *dev, bool shutdown)
{
	bool dead = true, freeze = false;
	struct pci_dev *pdev = to_pci_dev(dev->dev);

	mutex_lock(&dev->shutdown_lock);
	if (pci_is_enabled(pdev)) {
		u32 csts = readl(dev->bar + NVME_REG_CSTS);

		if (dev->ctrl.state == NVME_CTRL_LIVE ||
		    dev->ctrl.state == NVME_CTRL_RESETTING) {
			freeze = true;
			nvme_start_freeze(&dev->ctrl);
		}
		dead = !!((csts & NVME_CSTS_CFS) || !(csts & NVME_CSTS_RDY) ||
			pdev->error_state  != pci_channel_io_normal);
	}

	/*
	 * Give the controller a chance to complete all entered requests if
	 * doing a safe shutdown.
	 */
	if (!dead && shutdown && freeze)
		nvme_wait_freeze_timeout(&dev->ctrl, NVME_IO_TIMEOUT);

	nvme_stop_queues(&dev->ctrl);

	if (!dead && dev->ctrl.queue_count > 0) {
		nvme_disable_io_queues(dev);
		nvme_disable_admin_queue(dev, shutdown);
	}
	nvme_suspend_io_queues(dev);
	nvme_suspend_queue(&dev->queues[0]);
	nvme_pci_disable(dev);

	blk_mq_tagset_busy_iter(&dev->tagset, nvme_cancel_request, &dev->ctrl);
	blk_mq_tagset_busy_iter(&dev->admin_tagset, nvme_cancel_request, &dev->ctrl);
	blk_mq_tagset_wait_completed_request(&dev->tagset);
	blk_mq_tagset_wait_completed_request(&dev->admin_tagset);

	/*
	 * The driver will not be starting up queues again if shutting down so
	 * must flush all entered requests to their failed completion to avoid
	 * deadlocking blk-mq hot-cpu notifier.
	 */
	if (shutdown) {
		nvme_start_queues(&dev->ctrl);
		if (dev->ctrl.admin_q && !blk_queue_dying(dev->ctrl.admin_q))
			blk_mq_unquiesce_queue(dev->ctrl.admin_q);
	}
	mutex_unlock(&dev->shutdown_lock);
}