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
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  va; } ;
struct mt76_queue {TYPE_1__ rx_page; int /*<<< orphan*/  lock; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __page_frag_cache_drain (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* mt76_dma_dequeue (struct mt76_dev*,struct mt76_queue*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  skb_free_frag (void*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt76_dma_rx_cleanup(struct mt76_dev *dev, struct mt76_queue *q)
{
	struct page *page;
	void *buf;
	bool more;

	spin_lock_bh(&q->lock);
	do {
		buf = mt76_dma_dequeue(dev, q, true, NULL, NULL, &more);
		if (!buf)
			break;

		skb_free_frag(buf);
	} while (1);
	spin_unlock_bh(&q->lock);

	if (!q->rx_page.va)
		return;

	page = virt_to_page(q->rx_page.va);
	__page_frag_cache_drain(page, q->rx_page.pagecnt_bias);
	memset(&q->rx_page, 0, sizeof(q->rx_page));
}