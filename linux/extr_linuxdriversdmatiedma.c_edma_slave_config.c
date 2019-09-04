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
struct edma_chan {int /*<<< orphan*/  cfg; } ;
struct dma_slave_config {scalar_t__ src_addr_width; scalar_t__ dst_addr_width; scalar_t__ src_maxburst; scalar_t__ dst_maxburst; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ max_burst; } ;

/* Variables and functions */
 scalar_t__ DMA_SLAVE_BUSWIDTH_8_BYTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct edma_chan* to_edma_chan (struct dma_chan*) ; 

__attribute__((used)) static int edma_slave_config(struct dma_chan *chan,
	struct dma_slave_config *cfg)
{
	struct edma_chan *echan = to_edma_chan(chan);

	if (cfg->src_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES ||
	    cfg->dst_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES)
		return -EINVAL;

	if (cfg->src_maxburst > chan->device->max_burst ||
	    cfg->dst_maxburst > chan->device->max_burst)
		return -EINVAL;

	memcpy(&echan->cfg, cfg, sizeof(echan->cfg));

	return 0;
}