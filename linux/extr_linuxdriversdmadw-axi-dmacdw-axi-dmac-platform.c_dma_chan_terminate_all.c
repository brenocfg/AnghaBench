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
struct axi_dma_chan {TYPE_1__ vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_chan_disable (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_chan_name (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  dchan2dev (struct dma_chan*) ; 
 struct axi_dma_chan* dchan_to_axi_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dma_chan_terminate_all(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->vc.lock, flags);

	axi_chan_disable(chan);

	vchan_get_all_descriptors(&chan->vc, &head);

	/*
	 * As vchan_dma_desc_free_list can access to desc_allocated list
	 * we need to call it in vc.lock context.
	 */
	vchan_dma_desc_free_list(&chan->vc, &head);

	spin_unlock_irqrestore(&chan->vc.lock, flags);

	dev_vdbg(dchan2dev(dchan), "terminated: %s\n", axi_chan_name(chan));

	return 0;
}