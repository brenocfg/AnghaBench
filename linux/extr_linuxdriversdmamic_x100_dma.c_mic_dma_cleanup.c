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
typedef  size_t u32 ;
struct mic_dma_chan {size_t last_tail; int /*<<< orphan*/  cleanup_lock; struct dma_async_tx_descriptor* tx_array; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/ * callback; scalar_t__ cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_cookie_complete (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (struct dma_async_tx_descriptor*,int /*<<< orphan*/ *) ; 
 size_t mic_dma_hw_ring_inc (size_t) ; 
 size_t mic_dma_read_cmp_cnt (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mic_dma_cleanup(struct mic_dma_chan *ch)
{
	struct dma_async_tx_descriptor *tx;
	u32 tail;
	u32 last_tail;

	spin_lock(&ch->cleanup_lock);
	tail = mic_dma_read_cmp_cnt(ch);
	/*
	 * This is the barrier pair for smp_wmb() in fn.
	 * mic_dma_tx_submit_unlock. It's required so that we read the
	 * updated cookie value from tx->cookie.
	 */
	smp_rmb();
	for (last_tail = ch->last_tail; tail != last_tail;) {
		tx = &ch->tx_array[last_tail];
		if (tx->cookie) {
			dma_cookie_complete(tx);
			dmaengine_desc_get_callback_invoke(tx, NULL);
			tx->callback = NULL;
		}
		last_tail = mic_dma_hw_ring_inc(last_tail);
	}
	/* finish all completion callbacks before incrementing tail */
	smp_mb();
	ch->last_tail = last_tail;
	spin_unlock(&ch->cleanup_lock);
}