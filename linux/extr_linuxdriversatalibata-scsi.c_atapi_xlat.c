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
struct scsi_cmnd {scalar_t__ sc_data_direction; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; } ;
struct TYPE_2__ {int flags; unsigned int lbam; unsigned int lbah; int /*<<< orphan*/  feature; int /*<<< orphan*/  protocol; int /*<<< orphan*/  command; } ;
struct ata_queued_cmd {TYPE_1__ tf; int /*<<< orphan*/  complete_fn; int /*<<< orphan*/  cdb; struct ata_device* dev; struct scsi_cmnd* scsicmd; } ;
struct ata_device {int flags; int /*<<< orphan*/  cdb_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_DMADIR ; 
 int /*<<< orphan*/  ATAPI_PKT_DMA ; 
 int /*<<< orphan*/  ATAPI_PROT_DMA ; 
 int /*<<< orphan*/  ATAPI_PROT_NODATA ; 
 int /*<<< orphan*/  ATAPI_PROT_PIO ; 
 int /*<<< orphan*/  ATA_CMD_PACKET ; 
 int ATA_DFLAG_DMADIR ; 
 int ATA_DFLAG_PIO ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_WRITE ; 
 scalar_t__ DMA_NONE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  ata_qc_raw_nbytes (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_qc_set_pc_nbytes (struct ata_queued_cmd*) ; 
 scalar_t__ atapi_check_dma (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  atapi_qc_complete ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int atapi_xlat(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *scmd = qc->scsicmd;
	struct ata_device *dev = qc->dev;
	int nodata = (scmd->sc_data_direction == DMA_NONE);
	int using_pio = !nodata && (dev->flags & ATA_DFLAG_PIO);
	unsigned int nbytes;

	memset(qc->cdb, 0, dev->cdb_len);
	memcpy(qc->cdb, scmd->cmnd, scmd->cmd_len);

	qc->complete_fn = atapi_qc_complete;

	qc->tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	if (scmd->sc_data_direction == DMA_TO_DEVICE) {
		qc->tf.flags |= ATA_TFLAG_WRITE;
		DPRINTK("direction: write\n");
	}

	qc->tf.command = ATA_CMD_PACKET;
	ata_qc_set_pc_nbytes(qc);

	/* check whether ATAPI DMA is safe */
	if (!nodata && !using_pio && atapi_check_dma(qc))
		using_pio = 1;

	/* Some controller variants snoop this value for Packet
	 * transfers to do state machine and FIFO management.  Thus we
	 * want to set it properly, and for DMA where it is
	 * effectively meaningless.
	 */
	nbytes = min(ata_qc_raw_nbytes(qc), (unsigned int)63 * 1024);

	/* Most ATAPI devices which honor transfer chunk size don't
	 * behave according to the spec when odd chunk size which
	 * matches the transfer length is specified.  If the number of
	 * bytes to transfer is 2n+1.  According to the spec, what
	 * should happen is to indicate that 2n+1 is going to be
	 * transferred and transfer 2n+2 bytes where the last byte is
	 * padding.
	 *
	 * In practice, this doesn't happen.  ATAPI devices first
	 * indicate and transfer 2n bytes and then indicate and
	 * transfer 2 bytes where the last byte is padding.
	 *
	 * This inconsistency confuses several controllers which
	 * perform PIO using DMA such as Intel AHCIs and sil3124/32.
	 * These controllers use actual number of transferred bytes to
	 * update DMA poitner and transfer of 4n+2 bytes make those
	 * controller push DMA pointer by 4n+4 bytes because SATA data
	 * FISes are aligned to 4 bytes.  This causes data corruption
	 * and buffer overrun.
	 *
	 * Always setting nbytes to even number solves this problem
	 * because then ATAPI devices don't have to split data at 2n
	 * boundaries.
	 */
	if (nbytes & 0x1)
		nbytes++;

	qc->tf.lbam = (nbytes & 0xFF);
	qc->tf.lbah = (nbytes >> 8);

	if (nodata)
		qc->tf.protocol = ATAPI_PROT_NODATA;
	else if (using_pio)
		qc->tf.protocol = ATAPI_PROT_PIO;
	else {
		/* DMA data xfer */
		qc->tf.protocol = ATAPI_PROT_DMA;
		qc->tf.feature |= ATAPI_PKT_DMA;

		if ((dev->flags & ATA_DFLAG_DMADIR) &&
		    (scmd->sc_data_direction != DMA_TO_DEVICE))
			/* some SATA bridges need us to indicate data xfer direction */
			qc->tf.feature |= ATAPI_DMADIR;
	}


	/* FIXME: We need to translate 0x05 READ_BLOCK_LIMITS to a MODE_SENSE
	   as ATAPI tape drives don't get this right otherwise */
	return 0;
}