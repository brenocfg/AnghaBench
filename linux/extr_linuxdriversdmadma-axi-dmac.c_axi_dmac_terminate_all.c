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
struct dma_chan {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct axi_dmac_chan {TYPE_1__ vchan; int /*<<< orphan*/  active_descs; int /*<<< orphan*/ * next_desc; } ;
struct axi_dmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_DMAC_REG_CTRL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_dmac_write (struct axi_dmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axi_dmac* chan_to_axi_dmac (struct axi_dmac_chan*) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct axi_dmac_chan* to_axi_dmac_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int axi_dmac_terminate_all(struct dma_chan *c)
{
	struct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	struct axi_dmac *dmac = chan_to_axi_dmac(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	axi_dmac_write(dmac, AXI_DMAC_REG_CTRL, 0);
	chan->next_desc = NULL;
	vchan_get_all_descriptors(&chan->vchan, &head);
	list_splice_tail_init(&chan->active_descs, &head);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	vchan_dma_desc_free_list(&chan->vchan, &head);

	return 0;
}