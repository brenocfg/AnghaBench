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
struct aq_ring_s {size_t sw_head; size_t sw_tail; int /*<<< orphan*/  aq_nic; struct aq_ring_buff_s* buff_ring; } ;
struct aq_ring_buff_s {int /*<<< orphan*/  page; int /*<<< orphan*/  pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_CFG_RX_FRAME_MAX ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_nic_get_dev (int /*<<< orphan*/ ) ; 
 size_t aq_ring_next_dx (struct aq_ring_s*,size_t) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aq_ring_rx_deinit(struct aq_ring_s *self)
{
	if (!self)
		goto err_exit;

	for (; self->sw_head != self->sw_tail;
		self->sw_head = aq_ring_next_dx(self, self->sw_head)) {
		struct aq_ring_buff_s *buff = &self->buff_ring[self->sw_head];

		dma_unmap_page(aq_nic_get_dev(self->aq_nic), buff->pa,
			       AQ_CFG_RX_FRAME_MAX, DMA_FROM_DEVICE);

		__free_pages(buff->page, 0);
	}

err_exit:;
}