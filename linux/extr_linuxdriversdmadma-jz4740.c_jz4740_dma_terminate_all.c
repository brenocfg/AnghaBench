#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct jz4740_dmaengine_chan {TYPE_1__ vchan; int /*<<< orphan*/ * desc; int /*<<< orphan*/  id; } ;
struct jz4740_dma_dev {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_DMA_STATUS_CTRL_ENABLE ; 
 int /*<<< orphan*/  JZ_REG_DMA_STATUS_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 struct jz4740_dma_dev* jz4740_dma_chan_get_dev (struct jz4740_dmaengine_chan*) ; 
 int /*<<< orphan*/  jz4740_dma_write_mask (struct jz4740_dma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct jz4740_dmaengine_chan* to_jz4740_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jz4740_dma_terminate_all(struct dma_chan *c)
{
	struct jz4740_dmaengine_chan *chan = to_jz4740_dma_chan(c);
	struct jz4740_dma_dev *dmadev = jz4740_dma_chan_get_dev(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	jz4740_dma_write_mask(dmadev, JZ_REG_DMA_STATUS_CTRL(chan->id), 0,
			JZ_DMA_STATUS_CTRL_ENABLE);
	chan->desc = NULL;
	vchan_get_all_descriptors(&chan->vchan, &head);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	vchan_dma_desc_free_list(&chan->vchan, &head);

	return 0;
}