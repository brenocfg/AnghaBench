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
typedef  union sub_crq {int dummy; } sub_crq ;
struct ibmvnic_sub_crq_queue {int size; union sub_crq* msgs; int /*<<< orphan*/  msg_token; int /*<<< orphan*/  irq; int /*<<< orphan*/  hw_irq; int /*<<< orphan*/  crq_num; int /*<<< orphan*/  lock; struct ibmvnic_adapter* adapter; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  netdev; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int GFP_KERNEL ; 
 int H_CLOSED ; 
 int H_RESOURCE ; 
 int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,union sub_crq*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int h_reg_sub_crq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ibmvnic_reset_crq (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  kfree (struct ibmvnic_sub_crq_queue*) ; 
 struct ibmvnic_sub_crq_queue* kzalloc (int,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ibmvnic_sub_crq_queue *init_sub_crq_queue(struct ibmvnic_adapter
							*adapter)
{
	struct device *dev = &adapter->vdev->dev;
	struct ibmvnic_sub_crq_queue *scrq;
	int rc;

	scrq = kzalloc(sizeof(*scrq), GFP_KERNEL);
	if (!scrq)
		return NULL;

	scrq->msgs =
		(union sub_crq *)__get_free_pages(GFP_KERNEL | __GFP_ZERO, 2);
	if (!scrq->msgs) {
		dev_warn(dev, "Couldn't allocate crq queue messages page\n");
		goto zero_page_failed;
	}

	scrq->msg_token = dma_map_single(dev, scrq->msgs, 4 * PAGE_SIZE,
					 DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, scrq->msg_token)) {
		dev_warn(dev, "Couldn't map crq queue messages page\n");
		goto map_failed;
	}

	rc = h_reg_sub_crq(adapter->vdev->unit_address, scrq->msg_token,
			   4 * PAGE_SIZE, &scrq->crq_num, &scrq->hw_irq);

	if (rc == H_RESOURCE)
		rc = ibmvnic_reset_crq(adapter);

	if (rc == H_CLOSED) {
		dev_warn(dev, "Partner adapter not ready, waiting.\n");
	} else if (rc) {
		dev_warn(dev, "Error %d registering sub-crq\n", rc);
		goto reg_failed;
	}

	scrq->adapter = adapter;
	scrq->size = 4 * PAGE_SIZE / sizeof(*scrq->msgs);
	spin_lock_init(&scrq->lock);

	netdev_dbg(adapter->netdev,
		   "sub-crq initialized, num %lx, hw_irq=%lx, irq=%x\n",
		   scrq->crq_num, scrq->hw_irq, scrq->irq);

	return scrq;

reg_failed:
	dma_unmap_single(dev, scrq->msg_token, 4 * PAGE_SIZE,
			 DMA_BIDIRECTIONAL);
map_failed:
	free_pages((unsigned long)scrq->msgs, 2);
zero_page_failed:
	kfree(scrq);

	return NULL;
}