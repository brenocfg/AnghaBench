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
struct rcar_dmac_xfer_chunk {int /*<<< orphan*/  node; } ;
struct rcar_dmac_desc_page {int /*<<< orphan*/  node; struct rcar_dmac_xfer_chunk* chunks; } ;
struct TYPE_2__ {int /*<<< orphan*/  pages; int /*<<< orphan*/  chunks_free; } ;
struct rcar_dmac_chan {int /*<<< orphan*/  lock; TYPE_1__ desc; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 unsigned int RCAR_DMAC_XFER_CHUNKS_PER_PAGE ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rcar_dmac_xfer_chunk_alloc(struct rcar_dmac_chan *chan, gfp_t gfp)
{
	struct rcar_dmac_desc_page *page;
	unsigned long flags;
	LIST_HEAD(list);
	unsigned int i;

	page = (void *)get_zeroed_page(gfp);
	if (!page)
		return -ENOMEM;

	for (i = 0; i < RCAR_DMAC_XFER_CHUNKS_PER_PAGE; ++i) {
		struct rcar_dmac_xfer_chunk *chunk = &page->chunks[i];

		list_add_tail(&chunk->node, &list);
	}

	spin_lock_irqsave(&chan->lock, flags);
	list_splice_tail(&list, &chan->desc.chunks_free);
	list_add_tail(&page->node, &chan->desc.pages);
	spin_unlock_irqrestore(&chan->lock, flags);

	return 0;
}