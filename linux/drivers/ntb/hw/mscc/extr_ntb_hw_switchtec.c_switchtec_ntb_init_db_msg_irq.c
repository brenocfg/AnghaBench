#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct switchtec_ntb {void* doorbell_irq; void* message_irq; TYPE_3__* stdev; TYPE_2__* mmio_self_dbmsg; } ;
struct TYPE_6__ {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; TYPE_1__* mmio_part_cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/ * idb_vec_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  vep_vector_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  free_irq (void*,struct switchtec_ntb*) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 void* pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int request_irq (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct switchtec_ntb*) ; 
 int /*<<< orphan*/  switchtec_ntb_doorbell_isr ; 
 int /*<<< orphan*/  switchtec_ntb_message_isr ; 

__attribute__((used)) static int switchtec_ntb_init_db_msg_irq(struct switchtec_ntb *sndev)
{
	int i;
	int rc;
	int doorbell_irq = 0;
	int message_irq = 0;
	int event_irq;
	int idb_vecs = sizeof(sndev->mmio_self_dbmsg->idb_vec_map);

	event_irq = ioread32(&sndev->stdev->mmio_part_cfg->vep_vector_number);

	while (doorbell_irq == event_irq)
		doorbell_irq++;
	while (message_irq == doorbell_irq ||
	       message_irq == event_irq)
		message_irq++;

	dev_dbg(&sndev->stdev->dev, "irqs - event: %d, db: %d, msgs: %d\n",
		event_irq, doorbell_irq, message_irq);

	for (i = 0; i < idb_vecs - 4; i++)
		iowrite8(doorbell_irq,
			 &sndev->mmio_self_dbmsg->idb_vec_map[i]);

	for (; i < idb_vecs; i++)
		iowrite8(message_irq,
			 &sndev->mmio_self_dbmsg->idb_vec_map[i]);

	sndev->doorbell_irq = pci_irq_vector(sndev->stdev->pdev, doorbell_irq);
	sndev->message_irq = pci_irq_vector(sndev->stdev->pdev, message_irq);

	rc = request_irq(sndev->doorbell_irq,
			 switchtec_ntb_doorbell_isr, 0,
			 "switchtec_ntb_doorbell", sndev);
	if (rc)
		return rc;

	rc = request_irq(sndev->message_irq,
			 switchtec_ntb_message_isr, 0,
			 "switchtec_ntb_message", sndev);
	if (rc) {
		free_irq(sndev->doorbell_irq, sndev);
		return rc;
	}

	return 0;
}