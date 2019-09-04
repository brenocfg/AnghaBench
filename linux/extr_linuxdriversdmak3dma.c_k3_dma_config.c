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
typedef  int u32 ;
struct TYPE_3__ {int chan_id; } ;
struct TYPE_4__ {TYPE_1__ chan; } ;
struct k3_dma_chan {scalar_t__ dir; int ccfg; TYPE_2__ vc; int /*<<< orphan*/  dev_addr; } ;
struct dma_slave_config {scalar_t__ direction; int src_maxburst; int src_addr_width; int dst_maxburst; int dst_addr_width; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int CX_CFG_DSTINCR ; 
 int CX_CFG_EN ; 
 int CX_CFG_MEM2PER ; 
 int CX_CFG_SRCINCR ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 131 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 130 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_8_BYTES 128 
 int DMA_SLAVE_BUSWIDTH_UNDEFINED ; 
 int EINVAL ; 
 int __ffs (int) ; 
 struct k3_dma_chan* to_k3_chan (struct dma_chan*) ; 

__attribute__((used)) static int k3_dma_config(struct dma_chan *chan,
			 struct dma_slave_config *cfg)
{
	struct k3_dma_chan *c = to_k3_chan(chan);
	u32 maxburst = 0, val = 0;
	enum dma_slave_buswidth width = DMA_SLAVE_BUSWIDTH_UNDEFINED;

	if (cfg == NULL)
		return -EINVAL;
	c->dir = cfg->direction;
	if (c->dir == DMA_DEV_TO_MEM) {
		c->ccfg = CX_CFG_DSTINCR;
		c->dev_addr = cfg->src_addr;
		maxburst = cfg->src_maxburst;
		width = cfg->src_addr_width;
	} else if (c->dir == DMA_MEM_TO_DEV) {
		c->ccfg = CX_CFG_SRCINCR;
		c->dev_addr = cfg->dst_addr;
		maxburst = cfg->dst_maxburst;
		width = cfg->dst_addr_width;
	}
	switch (width) {
	case DMA_SLAVE_BUSWIDTH_1_BYTE:
	case DMA_SLAVE_BUSWIDTH_2_BYTES:
	case DMA_SLAVE_BUSWIDTH_4_BYTES:
	case DMA_SLAVE_BUSWIDTH_8_BYTES:
		val =  __ffs(width);
		break;
	default:
		val = 3;
		break;
	}
	c->ccfg |= (val << 12) | (val << 16);

	if ((maxburst == 0) || (maxburst > 16))
		val = 15;
	else
		val = maxburst - 1;
	c->ccfg |= (val << 20) | (val << 24);
	c->ccfg |= CX_CFG_MEM2PER | CX_CFG_EN;

	/* specific request line */
	c->ccfg |= c->vc.chan.chan_id << 4;

	return 0;
}