#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pages; int /*<<< orphan*/  chunks_free; } ;
struct rcar_dmac_chan {TYPE_1__ desc; } ;
struct dma_chan {TYPE_2__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int rcar_dmac_desc_alloc (struct rcar_dmac_chan*,int /*<<< orphan*/ ) ; 
 int rcar_dmac_xfer_chunk_alloc (struct rcar_dmac_chan*,int /*<<< orphan*/ ) ; 
 struct rcar_dmac_chan* to_rcar_dmac_chan (struct dma_chan*) ; 

__attribute__((used)) static int rcar_dmac_alloc_chan_resources(struct dma_chan *chan)
{
	struct rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	int ret;

	INIT_LIST_HEAD(&rchan->desc.chunks_free);
	INIT_LIST_HEAD(&rchan->desc.pages);

	/* Preallocate descriptors. */
	ret = rcar_dmac_xfer_chunk_alloc(rchan, GFP_KERNEL);
	if (ret < 0)
		return -ENOMEM;

	ret = rcar_dmac_desc_alloc(rchan, GFP_KERNEL);
	if (ret < 0)
		return -ENOMEM;

	return pm_runtime_get_sync(chan->device->dev);
}