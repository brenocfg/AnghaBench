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
typedef  enum sum_check_flags { ____Placeholder_sum_check_flags } sum_check_flags ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_PREP_PQ_DISABLE_P ; 
 unsigned long DMA_PREP_PQ_DISABLE_Q ; 
 int /*<<< orphan*/  IOAT_CHAN_DOWN ; 
 struct dma_async_tx_descriptor* __ioat_prep_pq16_lock (struct dma_chan*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned char const*,size_t,unsigned long) ; 
 struct dma_async_tx_descriptor* __ioat_prep_pq_lock (struct dma_chan*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned char const*,size_t,unsigned long) ; 
 int src_cnt_flags (unsigned int,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ioatdma_chan* to_ioat_chan (struct dma_chan*) ; 

struct dma_async_tx_descriptor *
ioat_prep_pq_val(struct dma_chan *chan, dma_addr_t *pq, dma_addr_t *src,
		  unsigned int src_cnt, const unsigned char *scf, size_t len,
		  enum sum_check_flags *pqres, unsigned long flags)
{
	struct ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		return NULL;

	/* specify valid address for disabled result */
	if (flags & DMA_PREP_PQ_DISABLE_P)
		pq[0] = pq[1];
	if (flags & DMA_PREP_PQ_DISABLE_Q)
		pq[1] = pq[0];

	/* the cleanup routine only sets bits on validate failure, it
	 * does not clear bits on validate success... so clear it here
	 */
	*pqres = 0;

	return src_cnt_flags(src_cnt, flags) > 8 ?
		__ioat_prep_pq16_lock(chan, pqres, pq, src, src_cnt, scf, len,
				       flags) :
		__ioat_prep_pq_lock(chan, pqres, pq, src, src_cnt, scf, len,
				     flags);
}