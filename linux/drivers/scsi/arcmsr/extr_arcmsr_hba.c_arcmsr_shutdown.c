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
struct Scsi_Host {scalar_t__ hostdata; } ;
struct AdapterControlBlock {int acb_flags; int /*<<< orphan*/  arcmsr_do_message_isr_bh; int /*<<< orphan*/  refresh_timer; int /*<<< orphan*/  eternal_timer; } ;

/* Variables and functions */
 int ACB_F_ADAPTER_REMOVED ; 
 int /*<<< orphan*/  arcmsr_disable_outbound_ints (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_flush_adapter_cache (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_irq (struct pci_dev*,struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_stop_adapter_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ set_date_time ; 

__attribute__((used)) static void arcmsr_shutdown(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	struct AdapterControlBlock *acb =
		(struct AdapterControlBlock *)host->hostdata;
	if (acb->acb_flags & ACB_F_ADAPTER_REMOVED)
		return;
	del_timer_sync(&acb->eternal_timer);
	if (set_date_time)
		del_timer_sync(&acb->refresh_timer);
	arcmsr_disable_outbound_ints(acb);
	arcmsr_free_irq(pdev, acb);
	flush_work(&acb->arcmsr_do_message_isr_bh);
	arcmsr_stop_adapter_bgrb(acb);
	arcmsr_flush_adapter_cache(acb);
}