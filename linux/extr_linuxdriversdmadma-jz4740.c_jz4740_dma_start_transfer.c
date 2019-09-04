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
struct virt_dma_desc {int dummy; } ;
struct jz4740_dmaengine_chan {size_t next_sg; int fifo_addr; int transfer_shift; int /*<<< orphan*/  id; TYPE_1__* desc; int /*<<< orphan*/  vchan; } ;
struct jz4740_dma_sg {int addr; int len; } ;
struct jz4740_dma_dev {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {size_t num_sgs; scalar_t__ direction; struct jz4740_dma_sg* sg; } ;

/* Variables and functions */
 scalar_t__ DMA_MEM_TO_DEV ; 
 int JZ_DMA_CTRL_ENABLE ; 
 int JZ_DMA_CTRL_HALT ; 
 int JZ_DMA_STATUS_CTRL_ENABLE ; 
 int JZ_DMA_STATUS_CTRL_HALT ; 
 int JZ_DMA_STATUS_CTRL_NO_DESC ; 
 int /*<<< orphan*/  JZ_REG_DMA_CTRL ; 
 int /*<<< orphan*/  JZ_REG_DMA_DST_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_REG_DMA_SRC_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_REG_DMA_STATUS_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_REG_DMA_TRANSFER_COUNT (int /*<<< orphan*/ ) ; 
 struct jz4740_dma_dev* jz4740_dma_chan_get_dev (struct jz4740_dmaengine_chan*) ; 
 int /*<<< orphan*/  jz4740_dma_write (struct jz4740_dma_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jz4740_dma_write_mask (struct jz4740_dma_dev*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* to_jz4740_dma_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jz4740_dma_start_transfer(struct jz4740_dmaengine_chan *chan)
{
	struct jz4740_dma_dev *dmadev = jz4740_dma_chan_get_dev(chan);
	dma_addr_t src_addr, dst_addr;
	struct virt_dma_desc *vdesc;
	struct jz4740_dma_sg *sg;

	jz4740_dma_write_mask(dmadev, JZ_REG_DMA_STATUS_CTRL(chan->id), 0,
			JZ_DMA_STATUS_CTRL_ENABLE);

	if (!chan->desc) {
		vdesc = vchan_next_desc(&chan->vchan);
		if (!vdesc)
			return 0;
		chan->desc = to_jz4740_dma_desc(vdesc);
		chan->next_sg = 0;
	}

	if (chan->next_sg == chan->desc->num_sgs)
		chan->next_sg = 0;

	sg = &chan->desc->sg[chan->next_sg];

	if (chan->desc->direction == DMA_MEM_TO_DEV) {
		src_addr = sg->addr;
		dst_addr = chan->fifo_addr;
	} else {
		src_addr = chan->fifo_addr;
		dst_addr = sg->addr;
	}
	jz4740_dma_write(dmadev, JZ_REG_DMA_SRC_ADDR(chan->id), src_addr);
	jz4740_dma_write(dmadev, JZ_REG_DMA_DST_ADDR(chan->id), dst_addr);
	jz4740_dma_write(dmadev, JZ_REG_DMA_TRANSFER_COUNT(chan->id),
			sg->len >> chan->transfer_shift);

	chan->next_sg++;

	jz4740_dma_write_mask(dmadev, JZ_REG_DMA_STATUS_CTRL(chan->id),
			JZ_DMA_STATUS_CTRL_NO_DESC | JZ_DMA_STATUS_CTRL_ENABLE,
			JZ_DMA_STATUS_CTRL_HALT | JZ_DMA_STATUS_CTRL_NO_DESC |
			JZ_DMA_STATUS_CTRL_ENABLE);

	jz4740_dma_write_mask(dmadev, JZ_REG_DMA_CTRL,
			JZ_DMA_CTRL_ENABLE,
			JZ_DMA_CTRL_HALT | JZ_DMA_CTRL_ENABLE);

	return 0;
}