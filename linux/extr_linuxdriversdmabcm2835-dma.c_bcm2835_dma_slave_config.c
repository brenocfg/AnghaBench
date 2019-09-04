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
struct dma_slave_config {scalar_t__ direction; scalar_t__ src_addr_width; scalar_t__ dst_addr_width; } ;
struct dma_chan {int dummy; } ;
struct bcm2835_chan {struct dma_slave_config cfg; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 scalar_t__ DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  is_slave_direction (scalar_t__) ; 
 struct bcm2835_chan* to_bcm2835_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int bcm2835_dma_slave_config(struct dma_chan *chan,
				    struct dma_slave_config *cfg)
{
	struct bcm2835_chan *c = to_bcm2835_dma_chan(chan);

	if ((cfg->direction == DMA_DEV_TO_MEM &&
	     cfg->src_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES) ||
	    (cfg->direction == DMA_MEM_TO_DEV &&
	     cfg->dst_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES) ||
	    !is_slave_direction(cfg->direction)) {
		return -EINVAL;
	}

	c->cfg = *cfg;

	return 0;
}