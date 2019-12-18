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
struct sw_rx_data {scalar_t__ page_offset; int /*<<< orphan*/  data; int /*<<< orphan*/  mapping; } ;
struct qede_rx_queue {scalar_t__ rx_buf_seg_size; int /*<<< orphan*/  data_direction; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_ref_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_alloc_rx_buffer (struct qede_rx_queue*,int) ; 
 int /*<<< orphan*/  qede_reuse_page (struct qede_rx_queue*,struct sw_rx_data*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qede_realloc_rx_buffer(struct qede_rx_queue *rxq,
					 struct sw_rx_data *curr_cons)
{
	/* Move to the next segment in the page */
	curr_cons->page_offset += rxq->rx_buf_seg_size;

	if (curr_cons->page_offset == PAGE_SIZE) {
		if (unlikely(qede_alloc_rx_buffer(rxq, true))) {
			/* Since we failed to allocate new buffer
			 * current buffer can be used again.
			 */
			curr_cons->page_offset -= rxq->rx_buf_seg_size;

			return -ENOMEM;
		}

		dma_unmap_page(rxq->dev, curr_cons->mapping,
			       PAGE_SIZE, rxq->data_direction);
	} else {
		/* Increment refcount of the page as we don't want
		 * network stack to take the ownership of the page
		 * which can be recycled multiple times by the driver.
		 */
		page_ref_inc(curr_cons->data);
		qede_reuse_page(rxq, curr_cons);
	}

	return 0;
}