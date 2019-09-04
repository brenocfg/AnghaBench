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
typedef  int u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct scsi_cmnd {int* cmnd; int cmd_len; } ;
struct ata_taskfile {int feature; int nsect; int auxiliary; int hob_feature; int lbah; int lbam; int lbal; int hob_lbah; int hob_lbam; int hob_lbal; int flags; int /*<<< orphan*/  device; int /*<<< orphan*/  command; int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {int hw_tag; struct ata_device* dev; struct scsi_cmnd* scsicmd; struct ata_taskfile tf; } ;
struct ata_device {int n_sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_NCQ_NON_DATA ; 
 int /*<<< orphan*/  ATA_CMD_ZAC_MGMT_OUT ; 
 int /*<<< orphan*/  ATA_LBA ; 
 int /*<<< orphan*/  ATA_PROT_NCQ_NODATA ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int ATA_SUBCMD_NCQ_NON_DATA_ZAC_MGMT_OUT ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int ZO_CLOSE_ZONE ; 
 int ZO_FINISH_ZONE ; 
 int ZO_OPEN_ZONE ; 
 int ZO_RESET_WRITE_POINTER ; 
 scalar_t__ ata_fpdma_zac_mgmt_out_supported (struct ata_device*) ; 
 scalar_t__ ata_ncq_enabled (struct ata_device*) ; 
 int /*<<< orphan*/  ata_scsi_set_invalid_field (struct ata_device*,struct scsi_cmnd*,int,int) ; 
 int /*<<< orphan*/  ata_scsi_set_sense (struct ata_device*,struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  scsi_16_lba_len (int const*,int*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int ata_scsi_zbc_out_xlat(struct ata_queued_cmd *qc)
{
	struct ata_taskfile *tf = &qc->tf;
	struct scsi_cmnd *scmd = qc->scsicmd;
	struct ata_device *dev = qc->dev;
	const u8 *cdb = scmd->cmnd;
	u8 all, sa;
	u64 block;
	u32 n_block;
	u16 fp = (u16)-1;

	if (unlikely(scmd->cmd_len < 16)) {
		fp = 15;
		goto invalid_fld;
	}

	sa = cdb[1] & 0x1f;
	if ((sa != ZO_CLOSE_ZONE) && (sa != ZO_FINISH_ZONE) &&
	    (sa != ZO_OPEN_ZONE) && (sa != ZO_RESET_WRITE_POINTER)) {
		fp = 1;
		goto invalid_fld;
	}

	scsi_16_lba_len(cdb, &block, &n_block);
	if (n_block) {
		/*
		 * ZAC MANAGEMENT OUT doesn't define any length
		 */
		goto invalid_param_len;
	}

	all = cdb[14] & 0x1;
	if (all) {
		/*
		 * Ignore the block address (zone ID) as defined by ZBC.
		 */
		block = 0;
	} else if (block >= dev->n_sectors) {
		/*
		 * Block must be a valid zone ID (a zone start LBA).
		 */
		fp = 2;
		goto invalid_fld;
	}

	if (ata_ncq_enabled(qc->dev) &&
	    ata_fpdma_zac_mgmt_out_supported(qc->dev)) {
		tf->protocol = ATA_PROT_NCQ_NODATA;
		tf->command = ATA_CMD_NCQ_NON_DATA;
		tf->feature = ATA_SUBCMD_NCQ_NON_DATA_ZAC_MGMT_OUT;
		tf->nsect = qc->hw_tag << 3;
		tf->auxiliary = sa | ((u16)all << 8);
	} else {
		tf->protocol = ATA_PROT_NODATA;
		tf->command = ATA_CMD_ZAC_MGMT_OUT;
		tf->feature = sa;
		tf->hob_feature = all;
	}
	tf->lbah = (block >> 16) & 0xff;
	tf->lbam = (block >> 8) & 0xff;
	tf->lbal = block & 0xff;
	tf->hob_lbah = (block >> 40) & 0xff;
	tf->hob_lbam = (block >> 32) & 0xff;
	tf->hob_lbal = (block >> 24) & 0xff;
	tf->device = ATA_LBA;
	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_LBA48;

	return 0;

 invalid_fld:
	ata_scsi_set_invalid_field(qc->dev, scmd, fp, 0xff);
	return 1;
invalid_param_len:
	/* "Parameter list length error" */
	ata_scsi_set_sense(qc->dev, scmd, ILLEGAL_REQUEST, 0x1a, 0x0);
	return 1;
}