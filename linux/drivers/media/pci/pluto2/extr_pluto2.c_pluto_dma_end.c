#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pluto {int* dma_buf; int /*<<< orphan*/  dma_addr; TYPE_1__* pdev; int /*<<< orphan*/  demux; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  TS_DMA_BYTES ; 
 unsigned int TS_DMA_PACKETS ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_packets (int /*<<< orphan*/ *,int*,unsigned int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_reset_ts (struct pluto*,int) ; 
 int /*<<< orphan*/  pluto_set_dma_addr (struct pluto*) ; 

__attribute__((used)) static void pluto_dma_end(struct pluto *pluto, unsigned int nbpackets)
{
	/* synchronize the DMA transfer with the CPU
	 * first so that we see updated contents. */
	pci_dma_sync_single_for_cpu(pluto->pdev, pluto->dma_addr,
			TS_DMA_BYTES, PCI_DMA_FROMDEVICE);

	/* Workaround for broken hardware:
	 * [1] On startup NBPACKETS seems to contain an uninitialized value,
	 *     but no packets have been transferred.
	 * [2] Sometimes (actually very often) NBPACKETS stays at zero
	 *     although one packet has been transferred.
	 * [3] Sometimes (actually rarely), the card gets into an erroneous
	 *     mode where it continuously generates interrupts, claiming it
	 *     has received nbpackets>TS_DMA_PACKETS packets, but no packet
	 *     has been transferred. Only a reset seems to solve this
	 */
	if ((nbpackets == 0) || (nbpackets > TS_DMA_PACKETS)) {
		unsigned int i = 0;
		while (pluto->dma_buf[i] == 0x47)
			i += 188;
		nbpackets = i / 188;
		if (i == 0) {
			pluto_reset_ts(pluto, 1);
			dev_printk(KERN_DEBUG, &pluto->pdev->dev, "resetting TS because of invalid packet counter\n");
		}
	}

	dvb_dmx_swfilter_packets(&pluto->demux, pluto->dma_buf, nbpackets);

	/* clear the dma buffer. this is needed to be able to identify
	 * new valid ts packets above */
	memset(pluto->dma_buf, 0, nbpackets * 188);

	/* reset the dma address */
	pluto_set_dma_addr(pluto);

	/* sync the buffer and give it back to the card */
	pci_dma_sync_single_for_device(pluto->pdev, pluto->dma_addr,
			TS_DMA_BYTES, PCI_DMA_FROMDEVICE);
}