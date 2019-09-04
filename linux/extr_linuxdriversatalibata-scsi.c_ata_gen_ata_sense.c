#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct scsi_cmnd {unsigned char* sense_buffer; int result; } ;
struct ata_taskfile {int command; int /*<<< orphan*/  feature; } ;
struct ata_queued_cmd {struct ata_taskfile result_tf; int /*<<< orphan*/  err_mask; TYPE_2__* ap; struct scsi_cmnd* scsicmd; struct ata_device* dev; } ;
struct ata_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  print_id; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/ * error_handler; } ;

/* Variables and functions */
 int ABORTED_COMMAND ; 
 int ATA_BUSY ; 
 int ATA_DF ; 
 int ATA_DRQ ; 
 int ATA_ERR ; 
 int DRIVER_SENSE ; 
 int NOT_READY ; 
 int SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 scalar_t__ U64_MAX ; 
 scalar_t__ ata_dev_disabled (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_scsi_set_sense (struct ata_device*,struct scsi_cmnd*,int,int,int) ; 
 scalar_t__ ata_tf_read_block (struct ata_taskfile*,struct ata_device*) ; 
 int /*<<< orphan*/  ata_to_sense_error (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*,int*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_set_sense_information (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ata_gen_ata_sense(struct ata_queued_cmd *qc)
{
	struct ata_device *dev = qc->dev;
	struct scsi_cmnd *cmd = qc->scsicmd;
	struct ata_taskfile *tf = &qc->result_tf;
	unsigned char *sb = cmd->sense_buffer;
	int verbose = qc->ap->ops->error_handler == NULL;
	u64 block;
	u8 sense_key, asc, ascq;

	memset(sb, 0, SCSI_SENSE_BUFFERSIZE);

	cmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

	if (ata_dev_disabled(dev)) {
		/* Device disabled after error recovery */
		/* LOGICAL UNIT NOT READY, HARD RESET REQUIRED */
		ata_scsi_set_sense(dev, cmd, NOT_READY, 0x04, 0x21);
		return;
	}
	/* Use ata_to_sense_error() to map status register bits
	 * onto sense key, asc & ascq.
	 */
	if (qc->err_mask ||
	    tf->command & (ATA_BUSY | ATA_DF | ATA_ERR | ATA_DRQ)) {
		ata_to_sense_error(qc->ap->print_id, tf->command, tf->feature,
				   &sense_key, &asc, &ascq, verbose);
		ata_scsi_set_sense(dev, cmd, sense_key, asc, ascq);
	} else {
		/* Could not decode error */
		ata_dev_warn(dev, "could not decode error status 0x%x err_mask 0x%x\n",
			     tf->command, qc->err_mask);
		ata_scsi_set_sense(dev, cmd, ABORTED_COMMAND, 0, 0);
		return;
	}

	block = ata_tf_read_block(&qc->result_tf, dev);
	if (block == U64_MAX)
		return;

	scsi_set_sense_information(sb, SCSI_SENSE_BUFFERSIZE, block);
}