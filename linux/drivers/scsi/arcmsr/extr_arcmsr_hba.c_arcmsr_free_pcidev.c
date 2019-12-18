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
struct pci_dev {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct AdapterControlBlock {struct pci_dev* pdev; int /*<<< orphan*/  refresh_timer; int /*<<< orphan*/  eternal_timer; int /*<<< orphan*/  arcmsr_do_message_isr_bh; struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  arcmsr_free_ccb_pool (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_irq (struct pci_dev*,struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_sysfs_attr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_unmap_pciregion (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 scalar_t__ set_date_time ; 

__attribute__((used)) static void arcmsr_free_pcidev(struct AdapterControlBlock *acb)
{
	struct pci_dev *pdev;
	struct Scsi_Host *host;

	host = acb->host;
	arcmsr_free_sysfs_attr(acb);
	scsi_remove_host(host);
	flush_work(&acb->arcmsr_do_message_isr_bh);
	del_timer_sync(&acb->eternal_timer);
	if (set_date_time)
		del_timer_sync(&acb->refresh_timer);
	pdev = acb->pdev;
	arcmsr_free_irq(pdev, acb);
	arcmsr_free_ccb_pool(acb);
	arcmsr_unmap_pciregion(acb);
	pci_release_regions(pdev);
	scsi_host_put(host);
	pci_disable_device(pdev);
}