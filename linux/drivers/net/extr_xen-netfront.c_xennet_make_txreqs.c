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
struct xennet_gnttab_make_txreq {struct xen_netif_tx_request* tx; scalar_t__ size; struct page* page; struct sk_buff* skb; struct netfront_queue* queue; } ;
struct xen_netif_tx_request {int dummy; } ;
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct netfront_queue {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  gnttab_foreach_grant_in_range (struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ,struct xennet_gnttab_make_txreq*) ; 
 int /*<<< orphan*/  xennet_make_one_txreq ; 

__attribute__((used)) static struct xen_netif_tx_request *xennet_make_txreqs(
	struct netfront_queue *queue, struct xen_netif_tx_request *tx,
	struct sk_buff *skb, struct page *page,
	unsigned int offset, unsigned int len)
{
	struct xennet_gnttab_make_txreq info = {
		.queue = queue,
		.skb = skb,
		.tx = tx,
	};

	/* Skip unused frames from start of page */
	page += offset >> PAGE_SHIFT;
	offset &= ~PAGE_MASK;

	while (len) {
		info.page = page;
		info.size = 0;

		gnttab_foreach_grant_in_range(page, offset, len,
					      xennet_make_one_txreq,
					      &info);

		page++;
		offset = 0;
		len -= info.size;
	}

	return info.tx;
}