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
struct vio_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  unit_address; int /*<<< orphan*/  irq; } ;
struct ibmvnic_crq_queue {int active; int /*<<< orphan*/ * msgs; int /*<<< orphan*/  msg_token; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  netdev; struct vio_dev* vdev; struct ibmvnic_crq_queue crq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 long H_BUSY ; 
 int /*<<< orphan*/  H_FREE_CRQ ; 
 scalar_t__ H_IS_LONG_BUSY (long) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_crq_queue(struct ibmvnic_adapter *adapter)
{
	struct ibmvnic_crq_queue *crq = &adapter->crq;
	struct vio_dev *vdev = adapter->vdev;
	long rc;

	if (!crq->msgs)
		return;

	netdev_dbg(adapter->netdev, "Releasing CRQ\n");
	free_irq(vdev->irq, adapter);
	tasklet_kill(&adapter->tasklet);
	do {
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	} while (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	dma_unmap_single(&vdev->dev, crq->msg_token, PAGE_SIZE,
			 DMA_BIDIRECTIONAL);
	free_page((unsigned long)crq->msgs);
	crq->msgs = NULL;
	crq->active = false;
}