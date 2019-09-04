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
typedef  int u32 ;
struct xilinx_dma_chan {int err; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  XILINX_DMA_DMACR_RUNSTOP ; 
 int XILINX_DMA_DMASR_HALTED ; 
 int /*<<< orphan*/  XILINX_DMA_LOOP_COUNT ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMACR ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMASR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct xilinx_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ctrl_read (struct xilinx_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ctrl_set (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xilinx_dma_poll_timeout (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xilinx_dma_start(struct xilinx_dma_chan *chan)
{
	int err;
	u32 val;

	dma_ctrl_set(chan, XILINX_DMA_REG_DMACR, XILINX_DMA_DMACR_RUNSTOP);

	/* Wait for the hardware to start */
	err = xilinx_dma_poll_timeout(chan, XILINX_DMA_REG_DMASR, val,
				      !(val & XILINX_DMA_DMASR_HALTED), 0,
				      XILINX_DMA_LOOP_COUNT);

	if (err) {
		dev_err(chan->dev, "Cannot start channel %p: %x\n",
			chan, dma_ctrl_read(chan, XILINX_DMA_REG_DMASR));

		chan->err = true;
	}
}