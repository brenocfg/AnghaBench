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
typedef  int uint16_t ;
struct pci_dev {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct CommandControlBlock {scalar_t__ startdone; TYPE_1__* pcmd; } ;
struct AdapterControlBlock {int maxOutstanding; int maxFreeCCB; struct CommandControlBlock** pccb_pool; int /*<<< orphan*/  ccboutstandingcount; int /*<<< orphan*/  acb_flags; int /*<<< orphan*/  refresh_timer; int /*<<< orphan*/  eternal_timer; int /*<<< orphan*/  arcmsr_do_message_isr_bh; } ;
struct TYPE_2__ {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACB_F_ADAPTER_REMOVED ; 
 int /*<<< orphan*/  ACB_F_IOP_INITED ; 
 int /*<<< orphan*/  ACB_F_SCSISTOPADAPTER ; 
 scalar_t__ ARCMSR_CCB_ABORTED ; 
 scalar_t__ ARCMSR_CCB_START ; 
 int DID_ABORT ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int /*<<< orphan*/  arcmsr_abort_allcmd (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_ccb_complete (struct CommandControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_disable_outbound_ints (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_done4abort_postqueue (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_flush_adapter_cache (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_ccb_pool (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_irq (struct pci_dev*,struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_pcidev (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_sysfs_attr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_interrupt (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_remove_scsi_devices (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_stop_adapter_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_unmap_pciregion (struct AdapterControlBlock*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 scalar_t__ set_date_time ; 

__attribute__((used)) static void arcmsr_remove(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	struct AdapterControlBlock *acb =
		(struct AdapterControlBlock *) host->hostdata;
	int poll_count = 0;
	uint16_t dev_id;

	pci_read_config_word(pdev, PCI_DEVICE_ID, &dev_id);
	if (dev_id == 0xffff) {
		acb->acb_flags &= ~ACB_F_IOP_INITED;
		acb->acb_flags |= ACB_F_ADAPTER_REMOVED;
		arcmsr_remove_scsi_devices(acb);
		arcmsr_free_pcidev(acb);
		return;
	}
	arcmsr_free_sysfs_attr(acb);
	scsi_remove_host(host);
	flush_work(&acb->arcmsr_do_message_isr_bh);
	del_timer_sync(&acb->eternal_timer);
	if (set_date_time)
		del_timer_sync(&acb->refresh_timer);
	arcmsr_disable_outbound_ints(acb);
	arcmsr_stop_adapter_bgrb(acb);
	arcmsr_flush_adapter_cache(acb);	
	acb->acb_flags |= ACB_F_SCSISTOPADAPTER;
	acb->acb_flags &= ~ACB_F_IOP_INITED;

	for (poll_count = 0; poll_count < acb->maxOutstanding; poll_count++){
		if (!atomic_read(&acb->ccboutstandingcount))
			break;
		arcmsr_interrupt(acb);/* FIXME: need spinlock */
		msleep(25);
	}

	if (atomic_read(&acb->ccboutstandingcount)) {
		int i;

		arcmsr_abort_allcmd(acb);
		arcmsr_done4abort_postqueue(acb);
		for (i = 0; i < acb->maxFreeCCB; i++) {
			struct CommandControlBlock *ccb = acb->pccb_pool[i];
			if (ccb->startdone == ARCMSR_CCB_START) {
				ccb->startdone = ARCMSR_CCB_ABORTED;
				ccb->pcmd->result = DID_ABORT << 16;
				arcmsr_ccb_complete(ccb);
			}
		}
	}
	arcmsr_free_irq(pdev, acb);
	arcmsr_free_ccb_pool(acb);
	arcmsr_unmap_pciregion(acb);
	pci_release_regions(pdev);
	scsi_host_put(host);
	pci_disable_device(pdev);
}