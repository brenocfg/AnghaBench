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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct napi_struct {int dummy; } ;
struct gve_rx_slot_page_info {int page_offset; void* page_address; } ;

/* Variables and functions */
 int GVE_RX_PAD ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* napi_alloc_skb (struct napi_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *gve_rx_copy(struct net_device *dev,
				   struct napi_struct *napi,
				   struct gve_rx_slot_page_info *page_info,
				   u16 len)
{
	struct sk_buff *skb = napi_alloc_skb(napi, len);
	void *va = page_info->page_address + GVE_RX_PAD +
		   page_info->page_offset;

	if (unlikely(!skb))
		return NULL;

	__skb_put(skb, len);

	skb_copy_to_linear_data(skb, va, len);

	skb->protocol = eth_type_trans(skb, dev);
	return skb;
}