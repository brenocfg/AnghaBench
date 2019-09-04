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
struct ioatdma_chan {int /*<<< orphan*/  state; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOAT_CHAN_DOWN ; 
 struct dma_async_tx_descriptor* __ioat_prep_xor_lock (struct dma_chan*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,size_t,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ioatdma_chan* to_ioat_chan (struct dma_chan*) ; 

struct dma_async_tx_descriptor *
ioat_prep_xor(struct dma_chan *chan, dma_addr_t dest, dma_addr_t *src,
	       unsigned int src_cnt, size_t len, unsigned long flags)
{
	struct ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		return NULL;

	return __ioat_prep_xor_lock(chan, NULL, dest, src, src_cnt, len, flags);
}