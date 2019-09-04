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
typedef  int /*<<< orphan*/  u32 ;
struct ppc440spe_adma_desc_slot {int /*<<< orphan*/  hw_desc; int /*<<< orphan*/  flags; int /*<<< orphan*/  phys; } ;
struct ppc440spe_adma_chan {TYPE_1__* device; } ;
struct dma_regs {int /*<<< orphan*/  cpfpl; } ;
struct TYPE_2__ {size_t id; struct dma_regs* dma_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMA_LL_DBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_CDB_NO_INT ; 
 int /*<<< orphan*/  PPC440SPE_DESC_INT ; 
 struct ppc440spe_adma_desc_slot** chan_last_sub ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_cb (struct ppc440spe_adma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppc440spe_dma_put_desc(struct ppc440spe_adma_chan *chan,
		struct ppc440spe_adma_desc_slot *desc)
{
	u32 pcdb;
	struct dma_regs *dma_reg = chan->device->dma_reg;

	pcdb = desc->phys;
	if (!test_bit(PPC440SPE_DESC_INT, &desc->flags))
		pcdb |= DMA_CDB_NO_INT;

	chan_last_sub[chan->device->id] = desc;

	ADMA_LL_DBG(print_cb(chan, desc->hw_desc));

	iowrite32(pcdb, &dma_reg->cpfpl);
}