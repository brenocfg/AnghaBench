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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct dvb_demux {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  slist; } ;
struct av7110 {int ttbp; TYPE_2__* dev; TYPE_1__ pt; int /*<<< orphan*/  feeding1; struct dvb_demux demux1; struct dvb_demux demux; scalar_t__ full_ts; scalar_t__ grabbing; } ;
struct TYPE_4__ {int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC1R ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_VDP3 ; 
 int TS_BUFLEN ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_packets (struct dvb_demux*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_dma_sync_sg_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int saa7146_read (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpeirq(unsigned long cookie)
{
	struct av7110 *budget = (struct av7110 *)cookie;
	u8 *mem = (u8 *) (budget->grabbing);
	u32 olddma = budget->ttbp;
	u32 newdma = saa7146_read(budget->dev, PCI_VDP3);
	struct dvb_demux *demux = budget->full_ts ? &budget->demux : &budget->demux1;

	/* nearest lower position divisible by 188 */
	newdma -= newdma % 188;

	if (newdma >= TS_BUFLEN)
		return;

	budget->ttbp = newdma;

	if (!budget->feeding1 || (newdma == olddma))
		return;

	/* Ensure streamed PCI data is synced to CPU */
	pci_dma_sync_sg_for_cpu(budget->dev->pci, budget->pt.slist, budget->pt.nents, PCI_DMA_FROMDEVICE);

#if 0
	/* track rps1 activity */
	printk("vpeirq: %02x Event Counter 1 0x%04x\n",
	       mem[olddma],
	       saa7146_read(budget->dev, EC1R) & 0x3fff);
#endif

	if (newdma > olddma)
		/* no wraparound, dump olddma..newdma */
		dvb_dmx_swfilter_packets(demux, mem + olddma, (newdma - olddma) / 188);
	else {
		/* wraparound, dump olddma..buflen and 0..newdma */
		dvb_dmx_swfilter_packets(demux, mem + olddma, (TS_BUFLEN - olddma) / 188);
		dvb_dmx_swfilter_packets(demux, mem, newdma / 188);
	}
}