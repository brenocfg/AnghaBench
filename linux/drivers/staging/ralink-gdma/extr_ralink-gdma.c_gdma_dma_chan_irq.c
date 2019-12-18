#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct gdma_dmaengine_chan {int next_sg; TYPE_3__ vchan; int /*<<< orphan*/  id; struct gdma_dma_desc* desc; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct gdma_dma_dev {int /*<<< orphan*/  chan_issued; TYPE_2__ ddev; } ;
struct TYPE_9__ {int /*<<< orphan*/  node; } ;
struct gdma_dma_desc {int num_sgs; TYPE_4__ vdesc; TYPE_1__* sg; int /*<<< orphan*/  residue; scalar_t__ cyclic; } ;
struct TYPE_6__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gdma_next_desc (struct gdma_dmaengine_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_4__*) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (TYPE_4__*) ; 

__attribute__((used)) static void gdma_dma_chan_irq(struct gdma_dma_dev *dma_dev,
			      struct gdma_dmaengine_chan *chan)
{
	struct gdma_dma_desc *desc;
	unsigned long flags;
	int chan_issued;

	chan_issued = 0;
	spin_lock_irqsave(&chan->vchan.lock, flags);
	desc = chan->desc;
	if (desc) {
		if (desc->cyclic) {
			vchan_cyclic_callback(&desc->vdesc);
			if (chan->next_sg == desc->num_sgs)
				chan->next_sg = 0;
			chan_issued = 1;
		} else {
			desc->residue -= desc->sg[chan->next_sg - 1].len;
			if (chan->next_sg == desc->num_sgs) {
				list_del(&desc->vdesc.node);
				vchan_cookie_complete(&desc->vdesc);
				chan_issued = gdma_next_desc(chan);
			} else {
				chan_issued = 1;
			}
		}
	} else {
		dev_dbg(dma_dev->ddev.dev, "chan %d no desc to complete\n",
			chan->id);
	}
	if (chan_issued)
		set_bit(chan->id, &dma_dev->chan_issued);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
}