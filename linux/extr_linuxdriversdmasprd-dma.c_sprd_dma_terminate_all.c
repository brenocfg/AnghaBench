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
struct sprd_dma_chn {TYPE_1__ vc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprd_dma_stop (struct sprd_dma_chn*) ; 
 struct sprd_dma_chn* to_sprd_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sprd_dma_terminate_all(struct dma_chan *chan)
{
	struct sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&schan->vc.lock, flags);
	sprd_dma_stop(schan);

	vchan_get_all_descriptors(&schan->vc, &head);
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	vchan_dma_desc_free_list(&schan->vc, &head);
	return 0;
}