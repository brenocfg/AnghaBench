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
typedef  int u32 ;
struct xor_regs {int /*<<< orphan*/  ccbalr; } ;
struct ppc440spe_adma_chan {TYPE_1__* device; int /*<<< orphan*/  hw_chain_inited; } ;
struct dma_regs {int /*<<< orphan*/  acpl; } ;
struct TYPE_2__ {int id; struct xor_regs* xor_reg; struct dma_regs* dma_reg; } ;

/* Variables and functions */
 int DMA_CDB_MSK ; 
#define  PPC440SPE_DMA0_ID 130 
#define  PPC440SPE_DMA1_ID 129 
#define  PPC440SPE_XOR_ID 128 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32
ppc440spe_chan_get_current_descriptor(struct ppc440spe_adma_chan *chan)
{
	struct dma_regs *dma_reg;
	struct xor_regs *xor_reg;

	if (unlikely(!chan->hw_chain_inited))
		/* h/w descriptor chain is not initialized yet */
		return 0;

	switch (chan->device->id) {
	case PPC440SPE_DMA0_ID:
	case PPC440SPE_DMA1_ID:
		dma_reg = chan->device->dma_reg;
		return ioread32(&dma_reg->acpl) & (~DMA_CDB_MSK);
	case PPC440SPE_XOR_ID:
		xor_reg = chan->device->xor_reg;
		return ioread32be(&xor_reg->ccbalr);
	}
	return 0;
}