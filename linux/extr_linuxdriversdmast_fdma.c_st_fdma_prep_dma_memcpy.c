#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t length; scalar_t__ dstride; scalar_t__ sstride; } ;
struct st_fdma_hw_node {size_t nbytes; TYPE_3__ generic; void* daddr; void* saddr; int /*<<< orphan*/  control; scalar_t__ next; } ;
struct st_fdma_desc {int /*<<< orphan*/  vdesc; TYPE_2__* node; } ;
struct st_fdma_chan {int /*<<< orphan*/  vchan; TYPE_1__* fdev; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_5__ {struct st_fdma_hw_node* desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDMA_NODE_CTRL_DST_INCR ; 
 int /*<<< orphan*/  FDMA_NODE_CTRL_INT_EON ; 
 int /*<<< orphan*/  FDMA_NODE_CTRL_REQ_MAP_FREE_RUN ; 
 int /*<<< orphan*/  FDMA_NODE_CTRL_SRC_INCR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct st_fdma_desc* st_fdma_alloc_desc (struct st_fdma_chan*,int) ; 
 struct st_fdma_chan* to_st_fdma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *st_fdma_prep_dma_memcpy(
	struct dma_chan *chan,	dma_addr_t dst, dma_addr_t src,
	size_t len, unsigned long flags)
{
	struct st_fdma_chan *fchan;
	struct st_fdma_desc *fdesc;
	struct st_fdma_hw_node *hw_node;

	if (!len)
		return NULL;

	fchan = to_st_fdma_chan(chan);

	/* We only require a single descriptor */
	fdesc = st_fdma_alloc_desc(fchan, 1);
	if (!fdesc) {
		dev_err(fchan->fdev->dev, "no memory for desc\n");
		return NULL;
	}

	hw_node = fdesc->node[0].desc;
	hw_node->next = 0;
	hw_node->control = FDMA_NODE_CTRL_REQ_MAP_FREE_RUN;
	hw_node->control |= FDMA_NODE_CTRL_SRC_INCR;
	hw_node->control |= FDMA_NODE_CTRL_DST_INCR;
	hw_node->control |= FDMA_NODE_CTRL_INT_EON;
	hw_node->nbytes = len;
	hw_node->saddr = src;
	hw_node->daddr = dst;
	hw_node->generic.length = len;
	hw_node->generic.sstride = 0;
	hw_node->generic.dstride = 0;

	return vchan_tx_prep(&fchan->vchan, &fdesc->vdesc, flags);
}