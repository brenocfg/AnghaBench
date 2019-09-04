#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct seq_file {struct capi_ctr* private; } ;
struct TYPE_8__ {scalar_t__ manu; } ;
struct capi_ctr {TYPE_1__ profile; scalar_t__ driverdata; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_12__ {char** version; unsigned long cardname; TYPE_6__* card; } ;
typedef  TYPE_5__ avmctrl_info ;
struct TYPE_13__ {unsigned long name; unsigned long port; unsigned long irq; unsigned long membase; int cardtype; scalar_t__ csr; int /*<<< orphan*/  lock; TYPE_4__* dma; } ;
typedef  TYPE_6__ avmcard ;
struct TYPE_10__ {scalar_t__ dmaaddr; } ;
struct TYPE_9__ {scalar_t__ dmaaddr; } ;
struct TYPE_11__ {TYPE_3__ recvbuf; TYPE_2__ sendbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMCC_INTCSR ; 
 int /*<<< orphan*/  AMCC_RXLEN ; 
 int /*<<< orphan*/  AMCC_RXPTR ; 
 int /*<<< orphan*/  AMCC_TXLEN ; 
 int /*<<< orphan*/  AMCC_TXPTR ; 
 size_t VER_CARDTYPE ; 
 size_t VER_DRIVER ; 
 size_t VER_SERIAL ; 
#define  avm_b1isa 136 
#define  avm_b1pci 135 
#define  avm_b1pcmcia 134 
#define  avm_c2 133 
#define  avm_c4 132 
#define  avm_m1 131 
#define  avm_m2 130 
#define  avm_t1isa 129 
#define  avm_t1pci 128 
 scalar_t__ b1dma_readl (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int b1dma_proc_show(struct seq_file *m, void *v)
{
	struct capi_ctr *ctrl = m->private;
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);
	avmcard *card = cinfo->card;
	u8 flag;
	char *s;
	u32 txoff, txlen, rxoff, rxlen, csr;
	unsigned long flags;

	seq_printf(m, "%-16s %s\n", "name", card->name);
	seq_printf(m, "%-16s 0x%x\n", "io", card->port);
	seq_printf(m, "%-16s %d\n", "irq", card->irq);
	seq_printf(m, "%-16s 0x%lx\n", "membase", card->membase);
	switch (card->cardtype) {
	case avm_b1isa: s = "B1 ISA"; break;
	case avm_b1pci: s = "B1 PCI"; break;
	case avm_b1pcmcia: s = "B1 PCMCIA"; break;
	case avm_m1: s = "M1"; break;
	case avm_m2: s = "M2"; break;
	case avm_t1isa: s = "T1 ISA (HEMA)"; break;
	case avm_t1pci: s = "T1 PCI"; break;
	case avm_c4: s = "C4"; break;
	case avm_c2: s = "C2"; break;
	default: s = "???"; break;
	}
	seq_printf(m, "%-16s %s\n", "type", s);
	if ((s = cinfo->version[VER_DRIVER]) != NULL)
		seq_printf(m, "%-16s %s\n", "ver_driver", s);
	if ((s = cinfo->version[VER_CARDTYPE]) != NULL)
		seq_printf(m, "%-16s %s\n", "ver_cardtype", s);
	if ((s = cinfo->version[VER_SERIAL]) != NULL)
		seq_printf(m, "%-16s %s\n", "ver_serial", s);

	if (card->cardtype != avm_m1) {
		flag = ((u8 *)(ctrl->profile.manu))[3];
		if (flag)
			seq_printf(m, "%-16s%s%s%s%s%s%s%s\n",
				   "protocol",
				   (flag & 0x01) ? " DSS1" : "",
				   (flag & 0x02) ? " CT1" : "",
				   (flag & 0x04) ? " VN3" : "",
				   (flag & 0x08) ? " NI1" : "",
				   (flag & 0x10) ? " AUSTEL" : "",
				   (flag & 0x20) ? " ESS" : "",
				   (flag & 0x40) ? " 1TR6" : ""
				);
	}
	if (card->cardtype != avm_m1) {
		flag = ((u8 *)(ctrl->profile.manu))[5];
		if (flag)
			seq_printf(m, "%-16s%s%s%s%s\n",
				   "linetype",
				   (flag & 0x01) ? " point to point" : "",
				   (flag & 0x02) ? " point to multipoint" : "",
				   (flag & 0x08) ? " leased line without D-channel" : "",
				   (flag & 0x04) ? " leased line with D-channel" : ""
				);
	}
	seq_printf(m, "%-16s %s\n", "cardname", cinfo->cardname);


	spin_lock_irqsave(&card->lock, flags);

	txoff = (dma_addr_t)b1dma_readl(card, AMCC_TXPTR)-card->dma->sendbuf.dmaaddr;
	txlen = b1dma_readl(card, AMCC_TXLEN);

	rxoff = (dma_addr_t)b1dma_readl(card, AMCC_RXPTR)-card->dma->recvbuf.dmaaddr;
	rxlen = b1dma_readl(card, AMCC_RXLEN);

	csr  = b1dma_readl(card, AMCC_INTCSR);

	spin_unlock_irqrestore(&card->lock, flags);

	seq_printf(m, "%-16s 0x%lx\n", "csr (cached)", (unsigned long)card->csr);
	seq_printf(m, "%-16s 0x%lx\n", "csr", (unsigned long)csr);
	seq_printf(m, "%-16s %lu\n", "txoff", (unsigned long)txoff);
	seq_printf(m, "%-16s %lu\n", "txlen", (unsigned long)txlen);
	seq_printf(m, "%-16s %lu\n", "rxoff", (unsigned long)rxoff);
	seq_printf(m, "%-16s %lu\n", "rxlen", (unsigned long)rxlen);

	return 0;
}