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
struct sk_buff {int /*<<< orphan*/  csum_level; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct net_device {int features; } ;
struct napi_struct {int dummy; } ;
struct be_rx_obj {struct be_adapter* adapter; } ;
struct be_rx_compl_info {int /*<<< orphan*/  vlan_tag; scalar_t__ vlanf; int /*<<< orphan*/  tunneled; int /*<<< orphan*/  rss_hash; } ;
struct be_adapter {struct be_rx_obj* rx_obj; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_drops_no_skbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_RX_SKB_ALLOC_SIZE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_rx_compl_discard (struct be_rx_obj*,struct be_rx_compl_info*) ; 
 scalar_t__ csum_passed (struct be_rx_compl_info*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 TYPE_1__* rx_stats (struct be_rx_obj*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_fill_rx_data (struct be_rx_obj*,struct sk_buff*,struct be_rx_compl_info*) ; 
 int /*<<< orphan*/  skb_mark_napi_id (struct sk_buff*,struct napi_struct*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void be_rx_compl_process(struct be_rx_obj *rxo, struct napi_struct *napi,
				struct be_rx_compl_info *rxcp)
{
	struct be_adapter *adapter = rxo->adapter;
	struct net_device *netdev = adapter->netdev;
	struct sk_buff *skb;

	skb = netdev_alloc_skb_ip_align(netdev, BE_RX_SKB_ALLOC_SIZE);
	if (unlikely(!skb)) {
		rx_stats(rxo)->rx_drops_no_skbs++;
		be_rx_compl_discard(rxo, rxcp);
		return;
	}

	skb_fill_rx_data(rxo, skb, rxcp);

	if (likely((netdev->features & NETIF_F_RXCSUM) && csum_passed(rxcp)))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	else
		skb_checksum_none_assert(skb);

	skb->protocol = eth_type_trans(skb, netdev);
	skb_record_rx_queue(skb, rxo - &adapter->rx_obj[0]);
	if (netdev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, rxcp->rss_hash, PKT_HASH_TYPE_L3);

	skb->csum_level = rxcp->tunneled;
	skb_mark_napi_id(skb, napi);

	if (rxcp->vlanf)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), rxcp->vlan_tag);

	netif_receive_skb(skb);
}