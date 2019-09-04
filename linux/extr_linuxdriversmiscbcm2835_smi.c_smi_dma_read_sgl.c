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
struct scatterlist {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct TYPE_2__ {scalar_t__ data_width; } ;
struct bcm2835_smi_instance {TYPE_1__ settings; int /*<<< orphan*/  dma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_ERROR ; 
 scalar_t__ SMI_WIDTH_8BIT ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_wait_for_async_tx (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  smi_disable (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* smi_dma_submit_sgl (struct bcm2835_smi_instance*,struct scatterlist*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smi_dump_context_labelled (struct bcm2835_smi_instance*,char*) ; 
 int /*<<< orphan*/  smi_init_programmed_read (struct bcm2835_smi_instance*,size_t) ; 

__attribute__((used)) static void
smi_dma_read_sgl(struct bcm2835_smi_instance *inst,
	struct scatterlist *sgl, size_t sg_len, size_t n_bytes)
{
	struct dma_async_tx_descriptor *desc;

	/* Disable SMI and set to read before dispatching DMA - if SMI is in
	 * write mode and TX fifo is empty, it will generate a DREQ which may
	 * cause the read DMA to complete before the SMI read command is even
	 * dispatched! We want to dispatch DMA before SMI read so that reading
	 * is gapless, for logic analyser.
	 */

	smi_disable(inst, DMA_DEV_TO_MEM);

	desc = smi_dma_submit_sgl(inst, sgl, sg_len, DMA_DEV_TO_MEM, NULL);
	dma_async_issue_pending(inst->dma_chan);

	if (inst->settings.data_width == SMI_WIDTH_8BIT)
		smi_init_programmed_read(inst, n_bytes);
	else
		smi_init_programmed_read(inst, n_bytes / 2);

	if (dma_wait_for_async_tx(desc) == DMA_ERROR)
		smi_dump_context_labelled(inst, "DMA timeout!");
}