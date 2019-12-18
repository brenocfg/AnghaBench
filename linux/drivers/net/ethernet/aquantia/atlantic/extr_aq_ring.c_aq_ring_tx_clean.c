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
struct device {int dummy; } ;
struct aq_ring_s {scalar_t__ sw_head; scalar_t__ hw_head; struct aq_ring_buff_s* buff_ring; int /*<<< orphan*/  aq_nic; } ;
struct aq_ring_buff_s {int eop_index; unsigned int pa; int /*<<< orphan*/  skb; int /*<<< orphan*/  is_eop; int /*<<< orphan*/  len; int /*<<< orphan*/  is_sop; int /*<<< orphan*/  is_mapped; } ;

/* Variables and functions */
 unsigned int AQ_CFG_TX_CLEAN_BUDGET ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct device* aq_nic_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_ring_dx_in_range (size_t,int,scalar_t__) ; 
 size_t aq_ring_next_dx (struct aq_ring_s*,size_t) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

bool aq_ring_tx_clean(struct aq_ring_s *self)
{
	struct device *dev = aq_nic_get_dev(self->aq_nic);
	unsigned int budget;

	for (budget = AQ_CFG_TX_CLEAN_BUDGET;
	     budget && self->sw_head != self->hw_head; budget--) {
		struct aq_ring_buff_s *buff = &self->buff_ring[self->sw_head];

		if (likely(buff->is_mapped)) {
			if (unlikely(buff->is_sop)) {
				if (!buff->is_eop &&
				    buff->eop_index != 0xffffU &&
				    (!aq_ring_dx_in_range(self->sw_head,
						buff->eop_index,
						self->hw_head)))
					break;

				dma_unmap_single(dev, buff->pa, buff->len,
						 DMA_TO_DEVICE);
			} else {
				dma_unmap_page(dev, buff->pa, buff->len,
					       DMA_TO_DEVICE);
			}
		}

		if (unlikely(buff->is_eop))
			dev_kfree_skb_any(buff->skb);

		buff->pa = 0U;
		buff->eop_index = 0xffffU;
		self->sw_head = aq_ring_next_dx(self, self->sw_head);
	}

	return !!budget;
}