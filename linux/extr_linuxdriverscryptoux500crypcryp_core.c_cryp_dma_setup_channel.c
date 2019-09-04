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
struct dma_slave_config {int dst_maxburst; int src_maxburst; int /*<<< orphan*/  src_addr_width; scalar_t__ src_addr; int /*<<< orphan*/  direction; int /*<<< orphan*/  dst_addr_width; scalar_t__ dst_addr; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cryp_dma_complete; void* chan_cryp2mem; void* chan_mem2cryp; int /*<<< orphan*/  cfg_cryp2mem; int /*<<< orphan*/  mask; int /*<<< orphan*/  cfg_mem2cryp; } ;
struct cryp_device_data {TYPE_1__ dma; scalar_t__ phybase; } ;

/* Variables and functions */
 scalar_t__ CRYP_DMA_RX_FIFO ; 
 scalar_t__ CRYP_DMA_TX_FIFO ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 void* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_slave_config (void*,struct dma_slave_config*) ; 
 int /*<<< orphan*/  engine_to_mem ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_to_engine ; 
 int /*<<< orphan*/  stedma40_filter ; 

__attribute__((used)) static void cryp_dma_setup_channel(struct cryp_device_data *device_data,
				   struct device *dev)
{
	struct dma_slave_config mem2cryp = {
		.direction = DMA_MEM_TO_DEV,
		.dst_addr = device_data->phybase + CRYP_DMA_TX_FIFO,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES,
		.dst_maxburst = 4,
	};
	struct dma_slave_config cryp2mem = {
		.direction = DMA_DEV_TO_MEM,
		.src_addr = device_data->phybase + CRYP_DMA_RX_FIFO,
		.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES,
		.src_maxburst = 4,
	};

	dma_cap_zero(device_data->dma.mask);
	dma_cap_set(DMA_SLAVE, device_data->dma.mask);

	device_data->dma.cfg_mem2cryp = mem_to_engine;
	device_data->dma.chan_mem2cryp =
		dma_request_channel(device_data->dma.mask,
				    stedma40_filter,
				    device_data->dma.cfg_mem2cryp);

	device_data->dma.cfg_cryp2mem = engine_to_mem;
	device_data->dma.chan_cryp2mem =
		dma_request_channel(device_data->dma.mask,
				    stedma40_filter,
				    device_data->dma.cfg_cryp2mem);

	dmaengine_slave_config(device_data->dma.chan_mem2cryp, &mem2cryp);
	dmaengine_slave_config(device_data->dma.chan_cryp2mem, &cryp2mem);

	init_completion(&device_data->dma.cryp_dma_complete);
}