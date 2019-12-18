#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ScsiReqBlk {int total_xfer_length; int sg_index; int sg_count; int sg_bus_addr; size_t request_length; int /*<<< orphan*/  state; int /*<<< orphan*/  status; int /*<<< orphan*/  adapter_status; struct DeviceCtlBlk* dcb; TYPE_3__* cmd; TYPE_2__* segment_x; } ;
struct SGentry {int dummy; } ;
struct DeviceCtlBlk {int sync_period; } ;
struct AdapterCtlBlk {struct ScsiReqBlk* tmp_srb; } ;
struct TYPE_8__ {TYPE_1__* device; } ;
struct TYPE_7__ {int address; int length; } ;
struct TYPE_6__ {scalar_t__ lun; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CFG2_WIDEFIFO ; 
 int CLRXFIFO ; 
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DBG_PIO ; 
 int DC395x_LASTPIO ; 
 int DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC395x_write32 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int DMACMD_DIR ; 
 int DMACMD_SG ; 
 int DO_DATALATCH ; 
 int /*<<< orphan*/  H_OVER_UNDER_RUN ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  OVER_RUN ; 
 int SCMD_DMA_IN ; 
 int SCMD_DMA_OUT ; 
 int SCMD_FIFO_IN ; 
 int SCMD_FIFO_OUT ; 
 int /*<<< orphan*/  SRB_DATA_XFER ; 
 int /*<<< orphan*/  SRB_XFERPAD ; 
 int /*<<< orphan*/  TRM_S1040_DMA_COMMAND ; 
 int /*<<< orphan*/  TRM_S1040_DMA_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_DMA_STATUS ; 
 int /*<<< orphan*/  TRM_S1040_DMA_XCNT ; 
 int /*<<< orphan*/  TRM_S1040_DMA_XHIGHADDR ; 
 int /*<<< orphan*/  TRM_S1040_DMA_XLOWADDR ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_COMMAND ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONFIG2 ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_COUNTER ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_FIFO ; 
 int WIDE_SYNC ; 
 int XFERPENDING ; 
 scalar_t__ debug_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ ,int,char,int,int,int) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dump_register_info (struct AdapterCtlBlk*,struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned char* scsi_kmap_atomic_sg (int /*<<< orphan*/ ,int,size_t*,size_t*) ; 
 int /*<<< orphan*/  scsi_kunmap_atomic_sg (unsigned char*) ; 
 scalar_t__ scsi_sg_count (TYPE_3__*) ; 
 int /*<<< orphan*/  scsi_sglist (TYPE_3__*) ; 
 int /*<<< orphan*/  sg_subtract_one (struct ScsiReqBlk*) ; 

__attribute__((used)) static void data_io_transfer(struct AdapterCtlBlk *acb, 
		struct ScsiReqBlk *srb, u16 io_dir)
{
	struct DeviceCtlBlk *dcb = srb->dcb;
	u8 bval;
	dprintkdbg(DBG_0,
		"data_io_transfer: (0x%p) <%02i-%i> %c len=%i, sg=(%i/%i)\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun,
		((io_dir & DMACMD_DIR) ? 'r' : 'w'),
		srb->total_xfer_length, srb->sg_index, srb->sg_count);
	if (srb == acb->tmp_srb)
		dprintkl(KERN_ERR, "data_io_transfer: Using tmp_srb!\n");
	if (srb->sg_index >= srb->sg_count) {
		/* can't happen? out of bounds error */
		return;
	}

	if (srb->total_xfer_length > DC395x_LASTPIO) {
		u8 dma_status = DC395x_read8(acb, TRM_S1040_DMA_STATUS);
		/*
		 * KG: What should we do: Use SCSI Cmd 0x90/0x92?
		 * Maybe, even ABORTXFER would be appropriate
		 */
		if (dma_status & XFERPENDING) {
			dprintkl(KERN_DEBUG, "data_io_transfer: Xfer pending! "
				"Expect trouble!\n");
			dump_register_info(acb, dcb, srb);
			DC395x_write8(acb, TRM_S1040_DMA_CONTROL, CLRXFIFO);
		}
		/* clear_fifo(acb, "IO"); */
		/* 
		 * load what physical address of Scatter/Gather list table
		 * want to be transfer
		 */
		srb->state |= SRB_DATA_XFER;
		DC395x_write32(acb, TRM_S1040_DMA_XHIGHADDR, 0);
		if (scsi_sg_count(srb->cmd)) {	/* with S/G */
			io_dir |= DMACMD_SG;
			DC395x_write32(acb, TRM_S1040_DMA_XLOWADDR,
				       srb->sg_bus_addr +
				       sizeof(struct SGentry) *
				       srb->sg_index);
			/* load how many bytes in the sg list table */
			DC395x_write32(acb, TRM_S1040_DMA_XCNT,
				       ((u32)(srb->sg_count -
					      srb->sg_index) << 3));
		} else {	/* without S/G */
			io_dir &= ~DMACMD_SG;
			DC395x_write32(acb, TRM_S1040_DMA_XLOWADDR,
				       srb->segment_x[0].address);
			DC395x_write32(acb, TRM_S1040_DMA_XCNT,
				       srb->segment_x[0].length);
		}
		/* load total transfer length (24bits) max value 16Mbyte */
		DC395x_write32(acb, TRM_S1040_SCSI_COUNTER,
			       srb->total_xfer_length);
		DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important for atn stop */
		if (io_dir & DMACMD_DIR) {	/* read */
			DC395x_write8(acb, TRM_S1040_SCSI_COMMAND,
				      SCMD_DMA_IN);
			DC395x_write16(acb, TRM_S1040_DMA_COMMAND, io_dir);
		} else {
			DC395x_write16(acb, TRM_S1040_DMA_COMMAND, io_dir);
			DC395x_write8(acb, TRM_S1040_SCSI_COMMAND,
				      SCMD_DMA_OUT);
		}

	}
#if DC395x_LASTPIO
	else if (srb->total_xfer_length > 0) {	/* The last four bytes: Do PIO */
		/* 
		 * load what physical address of Scatter/Gather list table
		 * want to be transfer
		 */
		srb->state |= SRB_DATA_XFER;
		/* load total transfer length (24bits) max value 16Mbyte */
		DC395x_write32(acb, TRM_S1040_SCSI_COUNTER,
			       srb->total_xfer_length);
		DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important for atn stop */
		if (io_dir & DMACMD_DIR) {	/* read */
			DC395x_write8(acb, TRM_S1040_SCSI_COMMAND,
				      SCMD_FIFO_IN);
		} else {	/* write */
			int ln = srb->total_xfer_length;
			size_t left_io = srb->total_xfer_length;

			if (srb->dcb->sync_period & WIDE_SYNC)
				DC395x_write8(acb, TRM_S1040_SCSI_CONFIG2,
				     CFG2_WIDEFIFO);

			while (left_io) {
				unsigned char *virt, *base = NULL;
				unsigned long flags = 0;
				size_t len = left_io;
				size_t offset = srb->request_length - left_io;

				local_irq_save(flags);
				/* Again, max 4 bytes */
				base = scsi_kmap_atomic_sg(scsi_sglist(srb->cmd),
							   srb->sg_count, &offset, &len);
				virt = base + offset;

				left_io -= len;

				while (len--) {
					if (debug_enabled(DBG_PIO))
						printk(" %02x", *virt);

					DC395x_write8(acb, TRM_S1040_SCSI_FIFO, *virt++);

					sg_subtract_one(srb);
				}

				scsi_kunmap_atomic_sg(base);
				local_irq_restore(flags);
			}
			if (srb->dcb->sync_period & WIDE_SYNC) {
				if (ln % 2) {
					DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 0);
					if (debug_enabled(DBG_PIO))
						printk(" |00");
				}
				DC395x_write8(acb, TRM_S1040_SCSI_CONFIG2, 0);
			}
			/*DC395x_write32(acb, TRM_S1040_SCSI_COUNTER, ln); */
			if (debug_enabled(DBG_PIO))
				printk("\n");
			DC395x_write8(acb, TRM_S1040_SCSI_COMMAND,
					  SCMD_FIFO_OUT);
		}
	}
#endif				/* DC395x_LASTPIO */
	else {		/* xfer pad */
		u8 data = 0, data2 = 0;
		if (srb->sg_count) {
			srb->adapter_status = H_OVER_UNDER_RUN;
			srb->status |= OVER_RUN;
		}
		/*
		 * KG: despite the fact that we are using 16 bits I/O ops
		 * the SCSI FIFO is only 8 bits according to the docs
		 * (we can set bit 1 in 0x8f to serialize FIFO access ...)
		 */
		if (dcb->sync_period & WIDE_SYNC) {
			DC395x_write32(acb, TRM_S1040_SCSI_COUNTER, 2);
			DC395x_write8(acb, TRM_S1040_SCSI_CONFIG2,
				      CFG2_WIDEFIFO);
			if (io_dir & DMACMD_DIR) {
				data = DC395x_read8(acb, TRM_S1040_SCSI_FIFO);
				data2 = DC395x_read8(acb, TRM_S1040_SCSI_FIFO);
			} else {
				/* Danger, Robinson: If you find KGs
				 * scattered over the wide disk, the driver
				 * or chip is to blame :-( */
				DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 'K');
				DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 'G');
			}
			DC395x_write8(acb, TRM_S1040_SCSI_CONFIG2, 0);
		} else {
			DC395x_write32(acb, TRM_S1040_SCSI_COUNTER, 1);
			/* Danger, Robinson: If you find a collection of Ks on your disk
			 * something broke :-( */
			if (io_dir & DMACMD_DIR)
				data = DC395x_read8(acb, TRM_S1040_SCSI_FIFO);
			else
				DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 'K');
		}
		srb->state |= SRB_XFERPAD;
		DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important for atn stop */
		/* SCSI command */
		bval = (io_dir & DMACMD_DIR) ? SCMD_FIFO_IN : SCMD_FIFO_OUT;
		DC395x_write8(acb, TRM_S1040_SCSI_COMMAND, bval);
	}
}