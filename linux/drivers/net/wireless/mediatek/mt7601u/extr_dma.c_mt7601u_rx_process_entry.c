#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct page {int dummy; } ;
struct mt7601u_dma_buf_rx {struct page* p; TYPE_1__* urb; } ;
struct mt7601u_dev {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7601U_STATE_INITIALIZED ; 
 int /*<<< orphan*/  MT_RX_ORDER ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* dev_alloc_pages (int /*<<< orphan*/ ) ; 
 int mt7601u_rx_next_seg_len (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mt7601u_rx_process_seg (struct mt7601u_dev*,int /*<<< orphan*/ *,int,struct page*) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mt_rx_dma_aggr (struct mt7601u_dev*,int,int) ; 

__attribute__((used)) static void
mt7601u_rx_process_entry(struct mt7601u_dev *dev, struct mt7601u_dma_buf_rx *e)
{
	u32 seg_len, data_len = e->urb->actual_length;
	u8 *data = page_address(e->p);
	struct page *new_p = NULL;
	int cnt = 0;

	if (!test_bit(MT7601U_STATE_INITIALIZED, &dev->state))
		return;

	/* Copy if there is very little data in the buffer. */
	if (data_len > 512)
		new_p = dev_alloc_pages(MT_RX_ORDER);

	while ((seg_len = mt7601u_rx_next_seg_len(data, data_len))) {
		mt7601u_rx_process_seg(dev, data, seg_len, new_p ? e->p : NULL);

		data_len -= seg_len;
		data += seg_len;
		cnt++;
	}

	if (cnt > 1)
		trace_mt_rx_dma_aggr(dev, cnt, !!new_p);

	if (new_p) {
		/* we have one extra ref from the allocator */
		__free_pages(e->p, MT_RX_ORDER);

		e->p = new_p;
	}
}