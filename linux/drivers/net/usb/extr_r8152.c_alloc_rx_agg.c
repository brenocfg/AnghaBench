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
struct rx_agg {int /*<<< orphan*/  page; int /*<<< orphan*/  info_list; int /*<<< orphan*/  list; struct r8152* context; int /*<<< orphan*/  urb; int /*<<< orphan*/  buffer; } ;
struct r8152 {int /*<<< orphan*/  rx_count; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_info; int /*<<< orphan*/  rx_buf_sz; struct net_device* netdev; } ;
struct TYPE_2__ {scalar_t__ parent; } ;
struct net_device {TYPE_1__ dev; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_COMP ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  alloc_pages (int,unsigned int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int dev_to_node (scalar_t__) ; 
 unsigned int get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rx_agg*) ; 
 struct rx_agg* kmalloc_node (int,int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct rx_agg *alloc_rx_agg(struct r8152 *tp, gfp_t mflags)
{
	struct net_device *netdev = tp->netdev;
	int node = netdev->dev.parent ? dev_to_node(netdev->dev.parent) : -1;
	unsigned int order = get_order(tp->rx_buf_sz);
	struct rx_agg *rx_agg;
	unsigned long flags;

	rx_agg = kmalloc_node(sizeof(*rx_agg), mflags, node);
	if (!rx_agg)
		return NULL;

	rx_agg->page = alloc_pages(mflags | __GFP_COMP, order);
	if (!rx_agg->page)
		goto free_rx;

	rx_agg->buffer = page_address(rx_agg->page);

	rx_agg->urb = usb_alloc_urb(0, mflags);
	if (!rx_agg->urb)
		goto free_buf;

	rx_agg->context = tp;

	INIT_LIST_HEAD(&rx_agg->list);
	INIT_LIST_HEAD(&rx_agg->info_list);
	spin_lock_irqsave(&tp->rx_lock, flags);
	list_add_tail(&rx_agg->info_list, &tp->rx_info);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	atomic_inc(&tp->rx_count);

	return rx_agg;

free_buf:
	__free_pages(rx_agg->page, order);
free_rx:
	kfree(rx_agg);
	return NULL;
}