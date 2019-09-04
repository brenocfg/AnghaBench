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
typedef  void* u8 ;
struct ata_taskfile {unsigned int nsect; unsigned int hob_nsect; int flags; void* lbam; void* lbal; int /*<<< orphan*/  protocol; int /*<<< orphan*/  command; } ;
struct ata_device {int horkage; int /*<<< orphan*/  id; scalar_t__ dma_mode; TYPE_2__* link; } ;
struct TYPE_4__ {TYPE_1__* ap; } ;
struct TYPE_3__ {unsigned long flags; } ;

/* Variables and functions */
 unsigned int AC_ERR_DEV ; 
 int /*<<< orphan*/  ATA_CMD_READ_LOG_DMA_EXT ; 
 int /*<<< orphan*/  ATA_CMD_READ_LOG_EXT ; 
 unsigned long ATA_FLAG_NO_LOG_PAGE ; 
 int ATA_HORKAGE_NO_DMA_LOG ; 
 int /*<<< orphan*/  ATA_PROT_DMA ; 
 int /*<<< orphan*/  ATA_PROT_PIO ; 
 unsigned int ATA_SECT_SIZE ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DPRINTK (char*,unsigned int,...) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*) ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_has_read_log_dma_ext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 

unsigned int ata_read_log_page(struct ata_device *dev, u8 log,
			       u8 page, void *buf, unsigned int sectors)
{
	unsigned long ap_flags = dev->link->ap->flags;
	struct ata_taskfile tf;
	unsigned int err_mask;
	bool dma = false;

	DPRINTK("read log page - log 0x%x, page 0x%x\n", log, page);

	/*
	 * Return error without actually issuing the command on controllers
	 * which e.g. lockup on a read log page.
	 */
	if (ap_flags & ATA_FLAG_NO_LOG_PAGE)
		return AC_ERR_DEV;

retry:
	ata_tf_init(dev, &tf);
	if (dev->dma_mode && ata_id_has_read_log_dma_ext(dev->id) &&
	    !(dev->horkage & ATA_HORKAGE_NO_DMA_LOG)) {
		tf.command = ATA_CMD_READ_LOG_DMA_EXT;
		tf.protocol = ATA_PROT_DMA;
		dma = true;
	} else {
		tf.command = ATA_CMD_READ_LOG_EXT;
		tf.protocol = ATA_PROT_PIO;
		dma = false;
	}
	tf.lbal = log;
	tf.lbam = page;
	tf.nsect = sectors;
	tf.hob_nsect = sectors >> 8;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_LBA48 | ATA_TFLAG_DEVICE;

	err_mask = ata_exec_internal(dev, &tf, NULL, DMA_FROM_DEVICE,
				     buf, sectors * ATA_SECT_SIZE, 0);

	if (err_mask && dma) {
		dev->horkage |= ATA_HORKAGE_NO_DMA_LOG;
		ata_dev_warn(dev, "READ LOG DMA EXT failed, trying PIO\n");
		goto retry;
	}

	DPRINTK("EXIT, err_mask=%x\n", err_mask);
	return err_mask;
}