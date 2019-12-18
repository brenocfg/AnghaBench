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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct myrb_sge {int dummy; } ;
struct myrb_hba {int /*<<< orphan*/  monitor_work; int /*<<< orphan*/  work_q; TYPE_1__* host; int /*<<< orphan*/ * sg_pool; int /*<<< orphan*/ * dcdb_pool; int /*<<< orphan*/  work_q_name; } ;
struct myrb_dcdb {int dummy; } ;
struct TYPE_2__ {size_t sg_tablesize; int host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myrb_monitor ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static bool myrb_create_mempools(struct pci_dev *pdev, struct myrb_hba *cb)
{
	size_t elem_size, elem_align;

	elem_align = sizeof(struct myrb_sge);
	elem_size = cb->host->sg_tablesize * elem_align;
	cb->sg_pool = dma_pool_create("myrb_sg", &pdev->dev,
				      elem_size, elem_align, 0);
	if (cb->sg_pool == NULL) {
		shost_printk(KERN_ERR, cb->host,
			     "Failed to allocate SG pool\n");
		return false;
	}

	cb->dcdb_pool = dma_pool_create("myrb_dcdb", &pdev->dev,
				       sizeof(struct myrb_dcdb),
				       sizeof(unsigned int), 0);
	if (!cb->dcdb_pool) {
		dma_pool_destroy(cb->sg_pool);
		cb->sg_pool = NULL;
		shost_printk(KERN_ERR, cb->host,
			     "Failed to allocate DCDB pool\n");
		return false;
	}

	snprintf(cb->work_q_name, sizeof(cb->work_q_name),
		 "myrb_wq_%d", cb->host->host_no);
	cb->work_q = create_singlethread_workqueue(cb->work_q_name);
	if (!cb->work_q) {
		dma_pool_destroy(cb->dcdb_pool);
		cb->dcdb_pool = NULL;
		dma_pool_destroy(cb->sg_pool);
		cb->sg_pool = NULL;
		shost_printk(KERN_ERR, cb->host,
			     "Failed to create workqueue\n");
		return false;
	}

	/*
	 * Initialize the Monitoring Timer.
	 */
	INIT_DELAYED_WORK(&cb->monitor_work, myrb_monitor);
	queue_delayed_work(cb->work_q, &cb->monitor_work, 1);

	return true;
}