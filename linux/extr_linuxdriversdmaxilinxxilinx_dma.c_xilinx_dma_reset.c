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
struct xilinx_dma_chan {int err; int idle; scalar_t__ desc_submitcount; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int XILINX_DMA_DMACR_RESET ; 
 int /*<<< orphan*/  XILINX_DMA_LOOP_COUNT ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMACR ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMASR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ctrl_read (struct xilinx_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ctrl_set (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int) ; 
 int xilinx_dma_poll_timeout (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xilinx_dma_reset(struct xilinx_dma_chan *chan)
{
	int err;
	u32 tmp;

	dma_ctrl_set(chan, XILINX_DMA_REG_DMACR, XILINX_DMA_DMACR_RESET);

	/* Wait for the hardware to finish reset */
	err = xilinx_dma_poll_timeout(chan, XILINX_DMA_REG_DMACR, tmp,
				      !(tmp & XILINX_DMA_DMACR_RESET), 0,
				      XILINX_DMA_LOOP_COUNT);

	if (err) {
		dev_err(chan->dev, "reset timeout, cr %x, sr %x\n",
			dma_ctrl_read(chan, XILINX_DMA_REG_DMACR),
			dma_ctrl_read(chan, XILINX_DMA_REG_DMASR));
		return -ETIMEDOUT;
	}

	chan->err = false;
	chan->idle = true;
	chan->desc_submitcount = 0;

	return err;
}