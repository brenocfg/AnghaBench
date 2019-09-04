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
struct xilinx_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  active_list; int /*<<< orphan*/  done_list; int /*<<< orphan*/  pending_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xilinx_dma_free_desc_list (struct xilinx_dma_chan*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xilinx_dma_free_descriptors(struct xilinx_dma_chan *chan)
{
	unsigned long flags;

	spin_lock_irqsave(&chan->lock, flags);

	xilinx_dma_free_desc_list(chan, &chan->pending_list);
	xilinx_dma_free_desc_list(chan, &chan->done_list);
	xilinx_dma_free_desc_list(chan, &chan->active_list);

	spin_unlock_irqrestore(&chan->lock, flags);
}