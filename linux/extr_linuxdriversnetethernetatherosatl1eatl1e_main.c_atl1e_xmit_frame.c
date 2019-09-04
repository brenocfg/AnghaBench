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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ protocol; } ;
struct net_device {int dummy; } ;
struct atl1e_tpd_desc {int word3; scalar_t__ word2; } ;
struct atl1e_adapter {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_VLAN_TAG_TO_TPD_TAG (scalar_t__,scalar_t__) ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int TPD_ETHTYPE_SHIFT ; 
 int TPD_INS_VL_TAG_SHIFT ; 
 scalar_t__ TPD_VLANTAG_MASK ; 
 scalar_t__ TPD_VLAN_SHIFT ; 
 int TPD_VL_TAGGED_SHIFT ; 
 int /*<<< orphan*/  __AT_DOWN ; 
 scalar_t__ atl1e_cal_tdp_req (struct sk_buff*) ; 
 struct atl1e_tpd_desc* atl1e_get_tpd (struct atl1e_adapter*) ; 
 scalar_t__ atl1e_tpd_avail (struct atl1e_adapter*) ; 
 scalar_t__ atl1e_tso_csum (struct atl1e_adapter*,struct sk_buff*,struct atl1e_tpd_desc*) ; 
 scalar_t__ atl1e_tx_map (struct atl1e_adapter*,struct sk_buff*,struct atl1e_tpd_desc*) ; 
 int /*<<< orphan*/  atl1e_tx_queue (struct atl1e_adapter*,scalar_t__,struct atl1e_tpd_desc*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t atl1e_xmit_frame(struct sk_buff *skb,
					  struct net_device *netdev)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);
	u16 tpd_req = 1;
	struct atl1e_tpd_desc *tpd;

	if (test_bit(__AT_DOWN, &adapter->flags)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (unlikely(skb->len <= 0)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}
	tpd_req = atl1e_cal_tdp_req(skb);

	if (atl1e_tpd_avail(adapter) < tpd_req) {
		/* no enough descriptor, just stop queue */
		netif_stop_queue(netdev);
		return NETDEV_TX_BUSY;
	}

	tpd = atl1e_get_tpd(adapter);

	if (skb_vlan_tag_present(skb)) {
		u16 vlan_tag = skb_vlan_tag_get(skb);
		u16 atl1e_vlan_tag;

		tpd->word3 |= 1 << TPD_INS_VL_TAG_SHIFT;
		AT_VLAN_TAG_TO_TPD_TAG(vlan_tag, atl1e_vlan_tag);
		tpd->word2 |= (atl1e_vlan_tag & TPD_VLANTAG_MASK) <<
				TPD_VLAN_SHIFT;
	}

	if (skb->protocol == htons(ETH_P_8021Q))
		tpd->word3 |= 1 << TPD_VL_TAGGED_SHIFT;

	if (skb_network_offset(skb) != ETH_HLEN)
		tpd->word3 |= 1 << TPD_ETHTYPE_SHIFT; /* 802.3 frame */

	/* do TSO and check sum */
	if (atl1e_tso_csum(adapter, skb, tpd) != 0) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (atl1e_tx_map(adapter, skb, tpd)) {
		dev_kfree_skb_any(skb);
		goto out;
	}

	atl1e_tx_queue(adapter, tpd_req, tpd);
out:
	return NETDEV_TX_OK;
}