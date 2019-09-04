#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct jz4740_dmaengine_chan {scalar_t__ next_sg; TYPE_1__ vchan; TYPE_2__* desc; } ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
struct TYPE_6__ {scalar_t__ num_sgs; TYPE_3__ vdesc; scalar_t__ cyclic; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4740_dma_start_transfer (struct jz4740_dmaengine_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_3__*) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (TYPE_3__*) ; 

__attribute__((used)) static void jz4740_dma_chan_irq(struct jz4740_dmaengine_chan *chan)
{
	spin_lock(&chan->vchan.lock);
	if (chan->desc) {
		if (chan->desc->cyclic) {
			vchan_cyclic_callback(&chan->desc->vdesc);
		} else {
			if (chan->next_sg == chan->desc->num_sgs) {
				list_del(&chan->desc->vdesc.node);
				vchan_cookie_complete(&chan->desc->vdesc);
				chan->desc = NULL;
			}
		}
	}
	jz4740_dma_start_transfer(chan);
	spin_unlock(&chan->vchan.lock);
}