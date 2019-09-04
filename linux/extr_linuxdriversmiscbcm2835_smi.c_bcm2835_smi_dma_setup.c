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
struct TYPE_3__ {int /*<<< orphan*/ * sgl; int /*<<< orphan*/ * phys; int /*<<< orphan*/ * buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  direction; scalar_t__ src_addr; scalar_t__ dst_addr; void* dst_addr_width; void* src_addr_width; } ;
struct bcm2835_smi_instance {TYPE_1__ bounce; int /*<<< orphan*/  dev; TYPE_2__ dma_config; int /*<<< orphan*/  dma_chan; scalar_t__ smi_regs_busaddr; } ;

/* Variables and functions */
 int DMA_BOUNCE_BUFFER_COUNT ; 
 int /*<<< orphan*/  DMA_BOUNCE_BUFFER_SIZE ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 void* DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SMID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_request_slave_channel (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmaengine_slave_config (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dmam_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_scatterlist_from_buffer (struct bcm2835_smi_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2835_smi_dma_setup(struct bcm2835_smi_instance *inst)
{
	int i, rv = 0;

	inst->dma_chan = dma_request_slave_channel(inst->dev, "rx-tx");

	inst->dma_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	inst->dma_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	inst->dma_config.src_addr = inst->smi_regs_busaddr + SMID;
	inst->dma_config.dst_addr = inst->dma_config.src_addr;
	/* Direction unimportant - always overridden by prep_slave_sg */
	inst->dma_config.direction = DMA_DEV_TO_MEM;
	dmaengine_slave_config(inst->dma_chan, &inst->dma_config);
	/* Alloc and map bounce buffers */
	for (i = 0; i < DMA_BOUNCE_BUFFER_COUNT; ++i) {
		inst->bounce.buffer[i] =
		dmam_alloc_coherent(inst->dev, DMA_BOUNCE_BUFFER_SIZE,
				&inst->bounce.phys[i],
				GFP_KERNEL);
		if (!inst->bounce.buffer[i]) {
			dev_err(inst->dev, "Could not allocate buffer!");
			rv = -ENOMEM;
			break;
		}
		smi_scatterlist_from_buffer(
			inst,
			inst->bounce.phys[i],
			DMA_BOUNCE_BUFFER_SIZE,
			&inst->bounce.sgl[i]
		);
	}

	return rv;
}