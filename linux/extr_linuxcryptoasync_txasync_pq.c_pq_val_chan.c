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
struct page {int dummy; } ;
struct dma_chan {int dummy; } ;
struct async_submit_ctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PQ_VAL ; 
 struct dma_chan* async_tx_find_channel (struct async_submit_ctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct page**,int,size_t) ; 

__attribute__((used)) static inline struct dma_chan *
pq_val_chan(struct async_submit_ctl *submit, struct page **blocks, int disks, size_t len)
{
	#ifdef CONFIG_ASYNC_TX_DISABLE_PQ_VAL_DMA
	return NULL;
	#endif
	return async_tx_find_channel(submit, DMA_PQ_VAL, NULL, 0,  blocks,
				     disks, len);
}