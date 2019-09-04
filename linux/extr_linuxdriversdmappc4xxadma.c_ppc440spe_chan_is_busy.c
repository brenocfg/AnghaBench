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
struct xor_regs {int /*<<< orphan*/  sr; } ;
struct ppc440spe_adma_chan {TYPE_1__* device; } ;
struct dma_regs {int /*<<< orphan*/  csftp; int /*<<< orphan*/  cpftp; int /*<<< orphan*/  cpfhp; } ;
struct TYPE_2__ {int id; struct xor_regs* xor_reg; struct dma_regs* dma_reg; } ;

/* Variables and functions */
#define  PPC440SPE_DMA0_ID 130 
#define  PPC440SPE_DMA1_ID 129 
#define  PPC440SPE_XOR_ID 128 
 int XOR_SR_XCP_BIT ; 
 int /*<<< orphan*/  ioread16 (int /*<<< orphan*/ *) ; 
 int ioread32be (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ppc440spe_chan_is_busy(struct ppc440spe_adma_chan *chan)
{
	struct dma_regs *dma_reg;
	struct xor_regs *xor_reg;
	int busy = 0;

	switch (chan->device->id) {
	case PPC440SPE_DMA0_ID:
	case PPC440SPE_DMA1_ID:
		dma_reg = chan->device->dma_reg;
		/*  if command FIFO's head and tail pointers are equal and
		 * status tail is the same as command, then channel is free
		 */
		if (ioread16(&dma_reg->cpfhp) != ioread16(&dma_reg->cpftp) ||
		    ioread16(&dma_reg->cpftp) != ioread16(&dma_reg->csftp))
			busy = 1;
		break;
	case PPC440SPE_XOR_ID:
		/* use the special status bit for the XORcore
		 */
		xor_reg = chan->device->xor_reg;
		busy = (ioread32be(&xor_reg->sr) & XOR_SR_XCP_BIT) ? 1 : 0;
		break;
	}

	return busy;
}