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
typedef  union ibmvnic_crq {int dummy; } ibmvnic_crq ;
struct device {int dummy; } ;
struct vio_dev {int unit_address; int /*<<< orphan*/  irq; struct device dev; } ;
struct ibmvnic_crq_queue {int size; union ibmvnic_crq* msgs; int /*<<< orphan*/  msg_token; int /*<<< orphan*/  lock; scalar_t__ cur; int /*<<< orphan*/  name; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  tasklet; struct vio_dev* vdev; int /*<<< orphan*/  netdev; struct ibmvnic_crq_queue crq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int H_BUSY ; 
 int H_CLOSED ; 
 int /*<<< orphan*/  H_FREE_CRQ ; 
 scalar_t__ H_IS_LONG_BUSY (int) ; 
 int /*<<< orphan*/  H_REG_CRQ ; 
 int H_RESOURCE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,union ibmvnic_crq*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvnic_interrupt ; 
 int ibmvnic_reset_crq (struct ibmvnic_adapter*) ; 
 scalar_t__ ibmvnic_tasklet ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int,...) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void*,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int vio_enable_interrupts (struct vio_dev*) ; 

__attribute__((used)) static int init_crq_queue(struct ibmvnic_adapter *adapter)
{
	struct ibmvnic_crq_queue *crq = &adapter->crq;
	struct device *dev = &adapter->vdev->dev;
	struct vio_dev *vdev = adapter->vdev;
	int rc, retrc = -ENOMEM;

	if (crq->msgs)
		return 0;

	crq->msgs = (union ibmvnic_crq *)get_zeroed_page(GFP_KERNEL);
	/* Should we allocate more than one page? */

	if (!crq->msgs)
		return -ENOMEM;

	crq->size = PAGE_SIZE / sizeof(*crq->msgs);
	crq->msg_token = dma_map_single(dev, crq->msgs, PAGE_SIZE,
					DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, crq->msg_token))
		goto map_failed;

	rc = plpar_hcall_norets(H_REG_CRQ, vdev->unit_address,
				crq->msg_token, PAGE_SIZE);

	if (rc == H_RESOURCE)
		/* maybe kexecing and resource is busy. try a reset */
		rc = ibmvnic_reset_crq(adapter);
	retrc = rc;

	if (rc == H_CLOSED) {
		dev_warn(dev, "Partner adapter not ready\n");
	} else if (rc) {
		dev_warn(dev, "Error %d opening adapter\n", rc);
		goto reg_crq_failed;
	}

	retrc = 0;

	tasklet_init(&adapter->tasklet, (void *)ibmvnic_tasklet,
		     (unsigned long)adapter);

	netdev_dbg(adapter->netdev, "registering irq 0x%x\n", vdev->irq);
	snprintf(crq->name, sizeof(crq->name), "ibmvnic-%x",
		 adapter->vdev->unit_address);
	rc = request_irq(vdev->irq, ibmvnic_interrupt, 0, crq->name, adapter);
	if (rc) {
		dev_err(dev, "Couldn't register irq 0x%x. rc=%d\n",
			vdev->irq, rc);
		goto req_irq_failed;
	}

	rc = vio_enable_interrupts(vdev);
	if (rc) {
		dev_err(dev, "Error %d enabling interrupts\n", rc);
		goto req_irq_failed;
	}

	crq->cur = 0;
	spin_lock_init(&crq->lock);

	return retrc;

req_irq_failed:
	tasklet_kill(&adapter->tasklet);
	do {
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	} while (rc == H_BUSY || H_IS_LONG_BUSY(rc));
reg_crq_failed:
	dma_unmap_single(dev, crq->msg_token, PAGE_SIZE, DMA_BIDIRECTIONAL);
map_failed:
	free_page((unsigned long)crq->msgs);
	crq->msgs = NULL;
	return retrc;
}