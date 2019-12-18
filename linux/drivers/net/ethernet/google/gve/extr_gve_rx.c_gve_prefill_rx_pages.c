#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct page {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data_ring; int /*<<< orphan*/ * page_info; TYPE_2__* qpl; } ;
struct gve_rx_ring {int mask; TYPE_1__ data; struct gve_priv* gve; } ;
struct gve_priv {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {struct page** pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 TYPE_2__* gve_assign_rx_qpl (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_setup_rx_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct page*) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gve_prefill_rx_pages(struct gve_rx_ring *rx)
{
	struct gve_priv *priv = rx->gve;
	u32 slots;
	int i;

	/* Allocate one page per Rx queue slot. Each page is split into two
	 * packet buffers, when possible we "page flip" between the two.
	 */
	slots = rx->mask + 1;

	rx->data.page_info = kvzalloc(slots *
				      sizeof(*rx->data.page_info), GFP_KERNEL);
	if (!rx->data.page_info)
		return -ENOMEM;

	rx->data.qpl = gve_assign_rx_qpl(priv);

	for (i = 0; i < slots; i++) {
		struct page *page = rx->data.qpl->pages[i];
		dma_addr_t addr = i * PAGE_SIZE;

		gve_setup_rx_buffer(&rx->data.page_info[i],
				    &rx->data.data_ring[i], addr, page);
	}

	return slots;
}