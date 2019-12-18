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
struct TYPE_2__ {int /*<<< orphan*/  opal_dev; scalar_t__ admin_q; } ;
struct nvme_dev {int /*<<< orphan*/  iod_mempool; TYPE_1__ ctrl; struct nvme_dev* queues; int /*<<< orphan*/  dev; } ;
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_put_queue (scalar_t__) ; 
 int /*<<< orphan*/  free_opal_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_dev*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_dbbuf_dma_free (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_free_tagset (struct nvme_dev*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 struct nvme_dev* to_nvme_dev (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_pci_free_ctrl(struct nvme_ctrl *ctrl)
{
	struct nvme_dev *dev = to_nvme_dev(ctrl);

	nvme_dbbuf_dma_free(dev);
	put_device(dev->dev);
	nvme_free_tagset(dev);
	if (dev->ctrl.admin_q)
		blk_put_queue(dev->ctrl.admin_q);
	kfree(dev->queues);
	free_opal_dev(dev->ctrl.opal_dev);
	mempool_destroy(dev->iod_mempool);
	kfree(dev);
}