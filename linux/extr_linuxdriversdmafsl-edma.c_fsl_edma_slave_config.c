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
struct TYPE_2__ {scalar_t__ dir; void* attr; int /*<<< orphan*/  burst; int /*<<< orphan*/  addr_width; int /*<<< orphan*/  dev_addr; } ;
struct fsl_edma_chan {TYPE_1__ fsc; } ;
struct dma_slave_config {scalar_t__ direction; int /*<<< orphan*/  dst_addr_width; int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  src_maxburst; int /*<<< orphan*/  src_addr; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int EINVAL ; 
 void* fsl_edma_get_tcd_attr (int /*<<< orphan*/ ) ; 
 struct fsl_edma_chan* to_fsl_edma_chan (struct dma_chan*) ; 

__attribute__((used)) static int fsl_edma_slave_config(struct dma_chan *chan,
				 struct dma_slave_config *cfg)
{
	struct fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);

	fsl_chan->fsc.dir = cfg->direction;
	if (cfg->direction == DMA_DEV_TO_MEM) {
		fsl_chan->fsc.dev_addr = cfg->src_addr;
		fsl_chan->fsc.addr_width = cfg->src_addr_width;
		fsl_chan->fsc.burst = cfg->src_maxburst;
		fsl_chan->fsc.attr = fsl_edma_get_tcd_attr(cfg->src_addr_width);
	} else if (cfg->direction == DMA_MEM_TO_DEV) {
		fsl_chan->fsc.dev_addr = cfg->dst_addr;
		fsl_chan->fsc.addr_width = cfg->dst_addr_width;
		fsl_chan->fsc.burst = cfg->dst_maxburst;
		fsl_chan->fsc.attr = fsl_edma_get_tcd_attr(cfg->dst_addr_width);
	} else {
			return -EINVAL;
	}
	return 0;
}