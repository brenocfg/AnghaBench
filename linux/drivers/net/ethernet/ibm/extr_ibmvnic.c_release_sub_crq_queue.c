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
struct ibmvnic_sub_crq_queue {scalar_t__ msgs; int /*<<< orphan*/  msg_token; int /*<<< orphan*/  crq_num; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  netdev; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 long H_BUSY ; 
 int /*<<< orphan*/  H_FREE_SUB_CRQ ; 
 scalar_t__ H_IS_LONG_BUSY (long) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  kfree (struct ibmvnic_sub_crq_queue*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long) ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_sub_crq_queue(struct ibmvnic_adapter *adapter,
				  struct ibmvnic_sub_crq_queue *scrq,
				  bool do_h_free)
{
	struct device *dev = &adapter->vdev->dev;
	long rc;

	netdev_dbg(adapter->netdev, "Releasing sub-CRQ\n");

	if (do_h_free) {
		/* Close the sub-crqs */
		do {
			rc = plpar_hcall_norets(H_FREE_SUB_CRQ,
						adapter->vdev->unit_address,
						scrq->crq_num);
		} while (rc == H_BUSY || H_IS_LONG_BUSY(rc));

		if (rc) {
			netdev_err(adapter->netdev,
				   "Failed to release sub-CRQ %16lx, rc = %ld\n",
				   scrq->crq_num, rc);
		}
	}

	dma_unmap_single(dev, scrq->msg_token, 4 * PAGE_SIZE,
			 DMA_BIDIRECTIONAL);
	free_pages((unsigned long)scrq->msgs, 2);
	kfree(scrq);
}