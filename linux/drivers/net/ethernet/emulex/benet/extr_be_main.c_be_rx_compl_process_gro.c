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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data_len; int /*<<< orphan*/  csum_level; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  truesize; } ;
struct napi_struct {int dummy; } ;
struct be_rx_page_info {scalar_t__ page_offset; int /*<<< orphan*/  page; } ;
struct be_rx_obj {struct be_adapter* adapter; } ;
struct be_rx_compl_info {scalar_t__ pkt_size; scalar_t__ num_rcvd; int /*<<< orphan*/  vlan_tag; scalar_t__ vlanf; int /*<<< orphan*/  tunneled; int /*<<< orphan*/  rss_hash; } ;
struct be_adapter {TYPE_1__* netdev; struct be_rx_obj* rx_obj; } ;
struct TYPE_4__ {scalar_t__ nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_rx_compl_discard (struct be_rx_obj*,struct be_rx_compl_info*) ; 
 struct be_rx_page_info* get_rx_page_info (struct be_rx_obj*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct be_rx_page_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct sk_buff* napi_get_frags (struct napi_struct*) ; 
 int /*<<< orphan*/  napi_gro_frags (struct napi_struct*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 scalar_t__ rx_frag_size ; 
 int /*<<< orphan*/  skb_frag_off_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_frag_set_page (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void be_rx_compl_process_gro(struct be_rx_obj *rxo,
				    struct napi_struct *napi,
				    struct be_rx_compl_info *rxcp)
{
	struct be_adapter *adapter = rxo->adapter;
	struct be_rx_page_info *page_info;
	struct sk_buff *skb = NULL;
	u16 remaining, curr_frag_len;
	u16 i, j;

	skb = napi_get_frags(napi);
	if (!skb) {
		be_rx_compl_discard(rxo, rxcp);
		return;
	}

	remaining = rxcp->pkt_size;
	for (i = 0, j = -1; i < rxcp->num_rcvd; i++) {
		page_info = get_rx_page_info(rxo);

		curr_frag_len = min(remaining, rx_frag_size);

		/* Coalesce all frags from the same physical page in one slot */
		if (i == 0 || page_info->page_offset == 0) {
			/* First frag or Fresh page */
			j++;
			skb_frag_set_page(skb, j, page_info->page);
			skb_frag_off_set(&skb_shinfo(skb)->frags[j],
					 page_info->page_offset);
			skb_frag_size_set(&skb_shinfo(skb)->frags[j], 0);
		} else {
			put_page(page_info->page);
		}
		skb_frag_size_add(&skb_shinfo(skb)->frags[j], curr_frag_len);
		skb->truesize += rx_frag_size;
		remaining -= curr_frag_len;
		memset(page_info, 0, sizeof(*page_info));
	}
	BUG_ON(j > MAX_SKB_FRAGS);

	skb_shinfo(skb)->nr_frags = j + 1;
	skb->len = rxcp->pkt_size;
	skb->data_len = rxcp->pkt_size;
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb_record_rx_queue(skb, rxo - &adapter->rx_obj[0]);
	if (adapter->netdev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, rxcp->rss_hash, PKT_HASH_TYPE_L3);

	skb->csum_level = rxcp->tunneled;

	if (rxcp->vlanf)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), rxcp->vlan_tag);

	napi_gro_frags(napi);
}