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
struct mv_xor_chan {int /*<<< orphan*/  dummy_dst_addr; int /*<<< orphan*/  dummy_src_addr; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t MV_XOR_MIN_BYTE_COUNT ; 
 struct dma_async_tx_descriptor* mv_xor_prep_dma_xor (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,size_t,unsigned long) ; 
 struct mv_xor_chan* to_mv_xor_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
mv_xor_prep_dma_interrupt(struct dma_chan *chan, unsigned long flags)
{
	struct mv_xor_chan *mv_chan = to_mv_xor_chan(chan);
	dma_addr_t src, dest;
	size_t len;

	src = mv_chan->dummy_src_addr;
	dest = mv_chan->dummy_dst_addr;
	len = MV_XOR_MIN_BYTE_COUNT;

	/*
	 * We implement the DMA_INTERRUPT operation as a minimum sized
	 * XOR operation with a single dummy source address.
	 */
	return mv_xor_prep_dma_xor(chan, dest, &src, 1, len, flags);
}