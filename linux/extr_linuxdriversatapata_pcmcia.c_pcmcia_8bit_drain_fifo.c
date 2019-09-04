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
struct ata_queued_cmd {scalar_t__ dma_dir; struct ata_port* ap; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_addr; } ;
struct ata_port {TYPE_2__ ioaddr; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* sff_check_status ) (struct ata_port*) ;} ;

/* Variables and functions */
 int ATA_DRQ ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ata_port_warn (struct ata_port*,char*,int) ; 
 int /*<<< orphan*/  ioread8 (int /*<<< orphan*/ ) ; 
 int stub1 (struct ata_port*) ; 

__attribute__((used)) static void pcmcia_8bit_drain_fifo(struct ata_queued_cmd *qc)
{
	int count;
	struct ata_port *ap;

	/* We only need to flush incoming data when a command was running */
	if (qc == NULL || qc->dma_dir == DMA_TO_DEVICE)
		return;

	ap = qc->ap;

	/* Drain up to 64K of data before we give up this recovery method */
	for (count = 0; (ap->ops->sff_check_status(ap) & ATA_DRQ)
							&& count++ < 65536;)
		ioread8(ap->ioaddr.data_addr);

	if (count)
		ata_port_warn(ap, "drained %d bytes to clear DRQ\n", count);

}