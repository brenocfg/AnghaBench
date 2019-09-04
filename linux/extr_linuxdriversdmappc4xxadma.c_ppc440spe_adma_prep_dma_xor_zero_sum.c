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
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum sum_check_flags { ____Placeholder_sum_check_flags } sum_check_flags ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_PREP_PQ_DISABLE_Q ; 
 struct dma_async_tx_descriptor* ppc440spe_adma_prep_dma_pqzero_sum (struct dma_chan*,scalar_t__*,scalar_t__*,unsigned int,int /*<<< orphan*/ ,size_t,int*,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *ppc440spe_adma_prep_dma_xor_zero_sum(
		struct dma_chan *chan, dma_addr_t *src, unsigned int src_cnt,
		size_t len, enum sum_check_flags *result, unsigned long flags)
{
	struct dma_async_tx_descriptor *tx;
	dma_addr_t pq[2];

	/* validate P, disable Q */
	pq[0] = src[0];
	pq[1] = 0;
	flags |= DMA_PREP_PQ_DISABLE_Q;

	tx = ppc440spe_adma_prep_dma_pqzero_sum(chan, pq, &src[1],
						src_cnt - 1, 0, len,
						result, flags);
	return tx;
}