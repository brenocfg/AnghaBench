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
struct dma_slave_config {int src_addr_width; scalar_t__ direction; } ;
struct moxart_chan {int line_reqno; scalar_t__ base; struct dma_slave_config cfg; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int APB_DMA_BURST_MODE ; 
 int APB_DMA_DATA_WIDTH ; 
 int APB_DMA_DATA_WIDTH_1 ; 
 int APB_DMA_DATA_WIDTH_2 ; 
 int APB_DMA_DEST_INC_1_4 ; 
 int APB_DMA_DEST_INC_2_8 ; 
 int APB_DMA_DEST_INC_4_16 ; 
 int APB_DMA_DEST_MASK ; 
 int APB_DMA_DEST_REQ_NO_MASK ; 
 int APB_DMA_DEST_SELECT ; 
 int APB_DMA_SOURCE_INC_1_4 ; 
 int APB_DMA_SOURCE_INC_2_8 ; 
 int APB_DMA_SOURCE_INC_4_16 ; 
 int APB_DMA_SOURCE_MASK ; 
 int APB_DMA_SOURCE_REQ_NO_MASK ; 
 int APB_DMA_SOURCE_SELECT ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 130 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 128 
 int EINVAL ; 
 scalar_t__ REG_OFF_CTRL ; 
 int readl (scalar_t__) ; 
 struct moxart_chan* to_moxart_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int moxart_slave_config(struct dma_chan *chan,
			       struct dma_slave_config *cfg)
{
	struct moxart_chan *ch = to_moxart_dma_chan(chan);
	u32 ctrl;

	ch->cfg = *cfg;

	ctrl = readl(ch->base + REG_OFF_CTRL);
	ctrl |= APB_DMA_BURST_MODE;
	ctrl &= ~(APB_DMA_DEST_MASK | APB_DMA_SOURCE_MASK);
	ctrl &= ~(APB_DMA_DEST_REQ_NO_MASK | APB_DMA_SOURCE_REQ_NO_MASK);

	switch (ch->cfg.src_addr_width) {
	case DMA_SLAVE_BUSWIDTH_1_BYTE:
		ctrl |= APB_DMA_DATA_WIDTH_1;
		if (ch->cfg.direction != DMA_MEM_TO_DEV)
			ctrl |= APB_DMA_DEST_INC_1_4;
		else
			ctrl |= APB_DMA_SOURCE_INC_1_4;
		break;
	case DMA_SLAVE_BUSWIDTH_2_BYTES:
		ctrl |= APB_DMA_DATA_WIDTH_2;
		if (ch->cfg.direction != DMA_MEM_TO_DEV)
			ctrl |= APB_DMA_DEST_INC_2_8;
		else
			ctrl |= APB_DMA_SOURCE_INC_2_8;
		break;
	case DMA_SLAVE_BUSWIDTH_4_BYTES:
		ctrl &= ~APB_DMA_DATA_WIDTH;
		if (ch->cfg.direction != DMA_MEM_TO_DEV)
			ctrl |= APB_DMA_DEST_INC_4_16;
		else
			ctrl |= APB_DMA_SOURCE_INC_4_16;
		break;
	default:
		return -EINVAL;
	}

	if (ch->cfg.direction == DMA_MEM_TO_DEV) {
		ctrl &= ~APB_DMA_DEST_SELECT;
		ctrl |= APB_DMA_SOURCE_SELECT;
		ctrl |= (ch->line_reqno << 16 &
			 APB_DMA_DEST_REQ_NO_MASK);
	} else {
		ctrl |= APB_DMA_DEST_SELECT;
		ctrl &= ~APB_DMA_SOURCE_SELECT;
		ctrl |= (ch->line_reqno << 24 &
			 APB_DMA_SOURCE_REQ_NO_MASK);
	}

	writel(ctrl, ch->base + REG_OFF_CTRL);

	return 0;
}