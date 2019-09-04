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
typedef  int /*<<< orphan*/  u32 ;
struct xilinx_dma_chan {int cyclic; int (* stop_transfer ) (struct xilinx_dma_chan*) ;int err; int idle; scalar_t__ has_sg; TYPE_2__* xdev; int /*<<< orphan*/  dev; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dma_config; } ;
struct TYPE_3__ {scalar_t__ dmatype; } ;

/* Variables and functions */
 scalar_t__ XDMA_TYPE_CDMA ; 
 int /*<<< orphan*/  XILINX_CDMA_CR_SGMODE ; 
 int /*<<< orphan*/  XILINX_DMA_CR_CYCLIC_BD_EN_MASK ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMACR ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMASR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct xilinx_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ctrl_clr (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ctrl_read (struct xilinx_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ctrl_write (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct xilinx_dma_chan*) ; 
 struct xilinx_dma_chan* to_xilinx_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  xilinx_dma_chan_reset (struct xilinx_dma_chan*) ; 
 int /*<<< orphan*/  xilinx_dma_free_descriptors (struct xilinx_dma_chan*) ; 

__attribute__((used)) static int xilinx_dma_terminate_all(struct dma_chan *dchan)
{
	struct xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	u32 reg;
	int err;

	if (chan->cyclic)
		xilinx_dma_chan_reset(chan);

	err = chan->stop_transfer(chan);
	if (err) {
		dev_err(chan->dev, "Cannot stop channel %p: %x\n",
			chan, dma_ctrl_read(chan, XILINX_DMA_REG_DMASR));
		chan->err = true;
	}

	/* Remove and free all of the descriptors in the lists */
	xilinx_dma_free_descriptors(chan);
	chan->idle = true;

	if (chan->cyclic) {
		reg = dma_ctrl_read(chan, XILINX_DMA_REG_DMACR);
		reg &= ~XILINX_DMA_CR_CYCLIC_BD_EN_MASK;
		dma_ctrl_write(chan, XILINX_DMA_REG_DMACR, reg);
		chan->cyclic = false;
	}

	if ((chan->xdev->dma_config->dmatype == XDMA_TYPE_CDMA) && chan->has_sg)
		dma_ctrl_clr(chan, XILINX_DMA_REG_DMACR,
			     XILINX_CDMA_CR_SGMODE);

	return 0;
}