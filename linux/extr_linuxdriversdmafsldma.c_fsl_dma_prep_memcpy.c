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
struct fsldma_chan {int dummy; } ;
struct dma_async_tx_descriptor {unsigned long flags; int /*<<< orphan*/  cookie; int /*<<< orphan*/  phys; } ;
struct fsl_desc_sw {int /*<<< orphan*/  tx_list; struct dma_async_tx_descriptor async_tx; int /*<<< orphan*/  node; int /*<<< orphan*/  hw; } ;
struct dma_chan {int dummy; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 scalar_t__ FSL_DMA_BCR_MAX_CNT ; 
 int /*<<< orphan*/  async_tx_ack (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  chan_err (struct fsldma_chan*,char*,int /*<<< orphan*/ ) ; 
 struct fsl_desc_sw* fsl_dma_alloc_descriptor (struct fsldma_chan*) ; 
 int /*<<< orphan*/  fsldma_free_desc_list_reverse (struct fsldma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  msg_ld_oom ; 
 int /*<<< orphan*/  set_desc_cnt (struct fsldma_chan*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  set_desc_dst (struct fsldma_chan*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  set_desc_next (struct fsldma_chan*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_desc_src (struct fsldma_chan*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  set_ld_eol (struct fsldma_chan*,struct fsl_desc_sw*) ; 
 struct fsldma_chan* to_fsl_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
fsl_dma_prep_memcpy(struct dma_chan *dchan,
	dma_addr_t dma_dst, dma_addr_t dma_src,
	size_t len, unsigned long flags)
{
	struct fsldma_chan *chan;
	struct fsl_desc_sw *first = NULL, *prev = NULL, *new;
	size_t copy;

	if (!dchan)
		return NULL;

	if (!len)
		return NULL;

	chan = to_fsl_chan(dchan);

	do {

		/* Allocate the link descriptor from DMA pool */
		new = fsl_dma_alloc_descriptor(chan);
		if (!new) {
			chan_err(chan, "%s\n", msg_ld_oom);
			goto fail;
		}

		copy = min(len, (size_t)FSL_DMA_BCR_MAX_CNT);

		set_desc_cnt(chan, &new->hw, copy);
		set_desc_src(chan, &new->hw, dma_src);
		set_desc_dst(chan, &new->hw, dma_dst);

		if (!first)
			first = new;
		else
			set_desc_next(chan, &prev->hw, new->async_tx.phys);

		new->async_tx.cookie = 0;
		async_tx_ack(&new->async_tx);

		prev = new;
		len -= copy;
		dma_src += copy;
		dma_dst += copy;

		/* Insert the link descriptor to the LD ring */
		list_add_tail(&new->node, &first->tx_list);
	} while (len);

	new->async_tx.flags = flags; /* client is in control of this ack */
	new->async_tx.cookie = -EBUSY;

	/* Set End-of-link to the last link descriptor of new list */
	set_ld_eol(chan, new);

	return &first->async_tx;

fail:
	if (!first)
		return NULL;

	fsldma_free_desc_list_reverse(chan, &first->tx_list);
	return NULL;
}