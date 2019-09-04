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
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct idma64_chan {TYPE_2__ vchan; TYPE_1__* desc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  idma64_chan_deactivate (struct idma64_chan*,int) ; 
 int /*<<< orphan*/  idma64_stop_transfer (struct idma64_chan*) ; 
 int /*<<< orphan*/  idma64_vdesc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct idma64_chan* to_idma64_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idma64_terminate_all(struct dma_chan *chan)
{
	struct idma64_chan *idma64c = to_idma64_chan(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&idma64c->vchan.lock, flags);
	idma64_chan_deactivate(idma64c, true);
	idma64_stop_transfer(idma64c);
	if (idma64c->desc) {
		idma64_vdesc_free(&idma64c->desc->vdesc);
		idma64c->desc = NULL;
	}
	vchan_get_all_descriptors(&idma64c->vchan, &head);
	spin_unlock_irqrestore(&idma64c->vchan.lock, flags);

	vchan_dma_desc_free_list(&idma64c->vchan, &head);
	return 0;
}