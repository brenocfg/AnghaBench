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
struct aq_ring_s {size_t sw_tail; int /*<<< orphan*/  aq_nic; struct aq_ring_buff_s* buff_ring; } ;
struct aq_ring_buff_s {unsigned int flags; int len; scalar_t__ page; int /*<<< orphan*/  pa; } ;

/* Variables and functions */
 int AQ_CFG_RX_FRAME_MAX ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int PAGE_SIZE ; 
 int __GFP_COMP ; 
 int /*<<< orphan*/  __free_pages (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ alloc_pages (int,unsigned int) ; 
 int /*<<< orphan*/  aq_nic_get_dev (int /*<<< orphan*/ ) ; 
 int aq_ring_avail_dx (struct aq_ring_s*) ; 
 size_t aq_ring_next_dx (struct aq_ring_s*,size_t) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fls (int) ; 

int aq_ring_rx_fill(struct aq_ring_s *self)
{
	unsigned int pages_order = fls(AQ_CFG_RX_FRAME_MAX / PAGE_SIZE +
		(AQ_CFG_RX_FRAME_MAX % PAGE_SIZE ? 1 : 0)) - 1;
	struct aq_ring_buff_s *buff = NULL;
	int err = 0;
	int i = 0;

	for (i = aq_ring_avail_dx(self); i--;
		self->sw_tail = aq_ring_next_dx(self, self->sw_tail)) {
		buff = &self->buff_ring[self->sw_tail];

		buff->flags = 0U;
		buff->len = AQ_CFG_RX_FRAME_MAX;

		buff->page = alloc_pages(GFP_ATOMIC | __GFP_COMP, pages_order);
		if (!buff->page) {
			err = -ENOMEM;
			goto err_exit;
		}

		buff->pa = dma_map_page(aq_nic_get_dev(self->aq_nic),
					buff->page, 0,
					AQ_CFG_RX_FRAME_MAX, DMA_FROM_DEVICE);

		if (dma_mapping_error(aq_nic_get_dev(self->aq_nic), buff->pa)) {
			err = -ENOMEM;
			goto err_exit;
		}

		buff = NULL;
	}

err_exit:
	if (err < 0) {
		if (buff && buff->page)
			__free_pages(buff->page, 0);
	}

	return err;
}