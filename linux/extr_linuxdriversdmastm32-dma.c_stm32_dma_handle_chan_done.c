#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stm32_dma_chan {scalar_t__ next_sg; int busy; TYPE_1__* desc; } ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
struct TYPE_4__ {scalar_t__ num_sgs; TYPE_2__ vdesc; scalar_t__ cyclic; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_dma_configure_next_sg (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  stm32_dma_start_transfer (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_2__*) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (TYPE_2__*) ; 

__attribute__((used)) static void stm32_dma_handle_chan_done(struct stm32_dma_chan *chan)
{
	if (chan->desc) {
		if (chan->desc->cyclic) {
			vchan_cyclic_callback(&chan->desc->vdesc);
			chan->next_sg++;
			stm32_dma_configure_next_sg(chan);
		} else {
			chan->busy = false;
			if (chan->next_sg == chan->desc->num_sgs) {
				list_del(&chan->desc->vdesc.node);
				vchan_cookie_complete(&chan->desc->vdesc);
				chan->desc = NULL;
			}
			stm32_dma_start_transfer(chan);
		}
	}
}