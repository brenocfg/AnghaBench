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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct CommandControlBlock {int /*<<< orphan*/  list; int /*<<< orphan*/  startdone; struct scsi_cmnd* pcmd; struct AdapterControlBlock* acb; } ;
struct AdapterControlBlock {int /*<<< orphan*/  ccblist_lock; int /*<<< orphan*/  ccb_free_list; int /*<<< orphan*/  ccboutstandingcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_CCB_DONE ; 
 int /*<<< orphan*/  arcmsr_pci_unmap_dma (struct CommandControlBlock*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void arcmsr_ccb_complete(struct CommandControlBlock *ccb)
{
	struct AdapterControlBlock *acb = ccb->acb;
	struct scsi_cmnd *pcmd = ccb->pcmd;
	unsigned long flags;
	atomic_dec(&acb->ccboutstandingcount);
	arcmsr_pci_unmap_dma(ccb);
	ccb->startdone = ARCMSR_CCB_DONE;
	spin_lock_irqsave(&acb->ccblist_lock, flags);
	list_add_tail(&ccb->list, &acb->ccb_free_list);
	spin_unlock_irqrestore(&acb->ccblist_lock, flags);
	pcmd->scsi_done(pcmd);
}