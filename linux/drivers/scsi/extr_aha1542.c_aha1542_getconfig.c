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
struct Scsi_Host {int dma_channel; int irq; int this_id; int /*<<< orphan*/  io_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RETCONF ; 
 int /*<<< orphan*/  DATA (int /*<<< orphan*/ ) ; 
 int DF ; 
 int /*<<< orphan*/  HACC ; 
 int /*<<< orphan*/  INTRFLAGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTRMASK ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aha1542_in (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aha1542_intr_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aha1542_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 int /*<<< orphan*/  wait_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aha1542_getconfig(struct Scsi_Host *sh)
{
	u8 inquiry_result[3];
	int i;
	i = inb(STATUS(sh->io_port));
	if (i & DF) {
		i = inb(DATA(sh->io_port));
	};
	aha1542_outb(sh->io_port, CMD_RETCONF);
	aha1542_in(sh->io_port, inquiry_result, 3, 0);
	if (!wait_mask(INTRFLAGS(sh->io_port), INTRMASK, HACC, 0, 0))
		shost_printk(KERN_ERR, sh, "error querying board settings\n");
	aha1542_intr_reset(sh->io_port);
	switch (inquiry_result[0]) {
	case 0x80:
		sh->dma_channel = 7;
		break;
	case 0x40:
		sh->dma_channel = 6;
		break;
	case 0x20:
		sh->dma_channel = 5;
		break;
	case 0x01:
		sh->dma_channel = 0;
		break;
	case 0:
		/* This means that the adapter, although Adaptec 1542 compatible, doesn't use a DMA channel.
		   Currently only aware of the BusLogic BT-445S VL-Bus adapter which needs this. */
		sh->dma_channel = 0xFF;
		break;
	default:
		shost_printk(KERN_ERR, sh, "Unable to determine DMA channel.\n");
		return -1;
	};
	switch (inquiry_result[1]) {
	case 0x40:
		sh->irq = 15;
		break;
	case 0x20:
		sh->irq = 14;
		break;
	case 0x8:
		sh->irq = 12;
		break;
	case 0x4:
		sh->irq = 11;
		break;
	case 0x2:
		sh->irq = 10;
		break;
	case 0x1:
		sh->irq = 9;
		break;
	default:
		shost_printk(KERN_ERR, sh, "Unable to determine IRQ level.\n");
		return -1;
	};
	sh->this_id = inquiry_result[2] & 7;
	return 0;
}