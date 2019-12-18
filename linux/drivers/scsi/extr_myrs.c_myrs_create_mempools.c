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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct myrs_sge {int dummy; } ;
struct myrs_hba {int /*<<< orphan*/  monitor_work; int /*<<< orphan*/  work_q; int /*<<< orphan*/ * sense_pool; int /*<<< orphan*/ * sg_pool; int /*<<< orphan*/ * dcdb_pool; int /*<<< orphan*/  work_q_name; struct Scsi_Host* host; } ;
struct Scsi_Host {size_t sg_tablesize; int host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 size_t MYRS_DCDB_SIZE ; 
 size_t MYRS_SENSE_SIZE ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myrs_monitor ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static bool myrs_create_mempools(struct pci_dev *pdev, struct myrs_hba *cs)
{
	struct Scsi_Host *shost = cs->host;
	size_t elem_size, elem_align;

	elem_align = sizeof(struct myrs_sge);
	elem_size = shost->sg_tablesize * elem_align;
	cs->sg_pool = dma_pool_create("myrs_sg", &pdev->dev,
				      elem_size, elem_align, 0);
	if (cs->sg_pool == NULL) {
		shost_printk(KERN_ERR, shost,
			     "Failed to allocate SG pool\n");
		return false;
	}

	cs->sense_pool = dma_pool_create("myrs_sense", &pdev->dev,
					 MYRS_SENSE_SIZE, sizeof(int), 0);
	if (cs->sense_pool == NULL) {
		dma_pool_destroy(cs->sg_pool);
		cs->sg_pool = NULL;
		shost_printk(KERN_ERR, shost,
			     "Failed to allocate sense data pool\n");
		return false;
	}

	cs->dcdb_pool = dma_pool_create("myrs_dcdb", &pdev->dev,
					MYRS_DCDB_SIZE,
					sizeof(unsigned char), 0);
	if (!cs->dcdb_pool) {
		dma_pool_destroy(cs->sg_pool);
		cs->sg_pool = NULL;
		dma_pool_destroy(cs->sense_pool);
		cs->sense_pool = NULL;
		shost_printk(KERN_ERR, shost,
			     "Failed to allocate DCDB pool\n");
		return false;
	}

	snprintf(cs->work_q_name, sizeof(cs->work_q_name),
		 "myrs_wq_%d", shost->host_no);
	cs->work_q = create_singlethread_workqueue(cs->work_q_name);
	if (!cs->work_q) {
		dma_pool_destroy(cs->dcdb_pool);
		cs->dcdb_pool = NULL;
		dma_pool_destroy(cs->sg_pool);
		cs->sg_pool = NULL;
		dma_pool_destroy(cs->sense_pool);
		cs->sense_pool = NULL;
		shost_printk(KERN_ERR, shost,
			     "Failed to create workqueue\n");
		return false;
	}

	/* Initialize the Monitoring Timer. */
	INIT_DELAYED_WORK(&cs->monitor_work, myrs_monitor);
	queue_delayed_work(cs->work_q, &cs->monitor_work, 1);

	return true;
}