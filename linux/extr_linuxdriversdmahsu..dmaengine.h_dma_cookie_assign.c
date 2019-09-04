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
struct dma_chan {scalar_t__ cookie; } ;
struct dma_async_tx_descriptor {scalar_t__ cookie; struct dma_chan* chan; } ;
typedef  scalar_t__ dma_cookie_t ;

/* Variables and functions */
 scalar_t__ DMA_MIN_COOKIE ; 

__attribute__((used)) static inline dma_cookie_t dma_cookie_assign(struct dma_async_tx_descriptor *tx)
{
	struct dma_chan *chan = tx->chan;
	dma_cookie_t cookie;

	cookie = chan->cookie + 1;
	if (cookie < DMA_MIN_COOKIE)
		cookie = DMA_MIN_COOKIE;
	tx->cookie = chan->cookie = cookie;

	return cookie;
}