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
struct scatterlist {int dummy; } ;
struct dma_async_tx_descriptor {struct bcm2835_smi_instance* callback_param; int /*<<< orphan*/  callback; } ;
struct bcm2835_smi_instance {int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_chan; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  int /*<<< orphan*/  dma_async_tx_callback ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int DMA_PREP_FENCE ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  SMICS ; 
 int SMICS_ACTIVE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,struct scatterlist*,size_t,int,int) ; 
 scalar_t__ dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_smi_reg (struct bcm2835_smi_instance*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct dma_async_tx_descriptor *smi_dma_submit_sgl(
	struct bcm2835_smi_instance *inst,
	struct scatterlist *sgl,
	size_t sg_len,
	enum dma_transfer_direction dir,
	dma_async_tx_callback callback)
{
	struct dma_async_tx_descriptor *desc;

	desc = dmaengine_prep_slave_sg(inst->dma_chan,
				       sgl,
				       sg_len,
				       dir,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK |
				       DMA_PREP_FENCE);
	if (!desc) {
		dev_err(inst->dev, "read_sgl: dma slave preparation failed!");
		write_smi_reg(inst, read_smi_reg(inst, SMICS) & ~SMICS_ACTIVE,
			SMICS);
		while (read_smi_reg(inst, SMICS) & SMICS_ACTIVE)
			cpu_relax();
		write_smi_reg(inst, read_smi_reg(inst, SMICS) | SMICS_ACTIVE,
			SMICS);
		return NULL;
	}
	desc->callback = callback;
	desc->callback_param = inst;
	if (dmaengine_submit(desc) < 0)
		return NULL;
	return desc;
}