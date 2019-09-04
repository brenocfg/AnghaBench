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
struct ppc440spe_adma_desc_slot {scalar_t__ phys; int /*<<< orphan*/  chain_node; int /*<<< orphan*/  slots_per_op; int /*<<< orphan*/  idx; struct dma_cdb* hw_desc; int /*<<< orphan*/  async_tx; } ;
struct ppc440spe_adma_chan {TYPE_2__* device; int /*<<< orphan*/  chain; } ;
struct dma_cdb {scalar_t__ opc; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ id; TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ DMA_CDB_OPC_DCHECK128 ; 
 scalar_t__ PPC440SPE_XOR_ID ; 
 int /*<<< orphan*/  async_tx_test_ack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppc440spe_adma_free_slots (struct ppc440spe_adma_desc_slot*,struct ppc440spe_adma_chan*) ; 
 scalar_t__ ppc440spe_chan_get_current_descriptor (struct ppc440spe_adma_chan*) ; 

__attribute__((used)) static int ppc440spe_adma_clean_slot(struct ppc440spe_adma_desc_slot *desc,
		struct ppc440spe_adma_chan *chan)
{
	/* the client is allowed to attach dependent operations
	 * until 'ack' is set
	 */
	if (!async_tx_test_ack(&desc->async_tx))
		return 0;

	/* leave the last descriptor in the chain
	 * so we can append to it
	 */
	if (list_is_last(&desc->chain_node, &chan->chain) ||
	    desc->phys == ppc440spe_chan_get_current_descriptor(chan))
		return 1;

	if (chan->device->id != PPC440SPE_XOR_ID) {
		/* our DMA interrupt handler clears opc field of
		 * each processed descriptor. For all types of
		 * operations except for ZeroSum we do not actually
		 * need ack from the interrupt handler. ZeroSum is a
		 * special case since the result of this operation
		 * is available from the handler only, so if we see
		 * such type of descriptor (which is unprocessed yet)
		 * then leave it in chain.
		 */
		struct dma_cdb *cdb = desc->hw_desc;
		if (cdb->opc == DMA_CDB_OPC_DCHECK128)
			return 1;
	}

	dev_dbg(chan->device->common.dev, "\tfree slot %llx: %d stride: %d\n",
		desc->phys, desc->idx, desc->slots_per_op);

	list_del(&desc->chain_node);
	ppc440spe_adma_free_slots(desc, chan);
	return 0;
}