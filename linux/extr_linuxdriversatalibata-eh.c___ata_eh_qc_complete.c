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
struct scsi_cmnd {int dummy; } ;
struct ata_queued_cmd {int /*<<< orphan*/  tag; int /*<<< orphan*/  scsidone; struct scsi_cmnd* scsicmd; struct ata_port* ap; } ;
struct ata_port {int /*<<< orphan*/  eh_done_q; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ata_qc_complete (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_eh_scsidone ; 
 int /*<<< orphan*/  ata_tag_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_eh_finish_cmd (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void __ata_eh_qc_complete(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct scsi_cmnd *scmd = qc->scsicmd;
	unsigned long flags;

	spin_lock_irqsave(ap->lock, flags);
	qc->scsidone = ata_eh_scsidone;
	__ata_qc_complete(qc);
	WARN_ON(ata_tag_valid(qc->tag));
	spin_unlock_irqrestore(ap->lock, flags);

	scsi_eh_finish_cmd(scmd, &ap->eh_done_q);
}