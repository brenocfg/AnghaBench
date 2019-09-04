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
struct scsi_device {int dummy; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;struct scsi_device* device; } ;
struct ata_port {int /*<<< orphan*/  lock; } ;
struct ata_device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int __ata_scsi_queuecmd (struct scsi_cmnd*,struct ata_device*) ; 
 int /*<<< orphan*/  ata_scsi_dump_cdb (struct ata_port*,struct scsi_cmnd*) ; 
 struct ata_device* ata_scsi_find_dev (struct ata_port*,struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (struct Scsi_Host*) ; 
 scalar_t__ likely (struct ata_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

int ata_scsi_queuecmd(struct Scsi_Host *shost, struct scsi_cmnd *cmd)
{
	struct ata_port *ap;
	struct ata_device *dev;
	struct scsi_device *scsidev = cmd->device;
	int rc = 0;
	unsigned long irq_flags;

	ap = ata_shost_to_port(shost);

	spin_lock_irqsave(ap->lock, irq_flags);

	ata_scsi_dump_cdb(ap, cmd);

	dev = ata_scsi_find_dev(ap, scsidev);
	if (likely(dev))
		rc = __ata_scsi_queuecmd(cmd, dev);
	else {
		cmd->result = (DID_BAD_TARGET << 16);
		cmd->scsi_done(cmd);
	}

	spin_unlock_irqrestore(ap->lock, irq_flags);

	return rc;
}