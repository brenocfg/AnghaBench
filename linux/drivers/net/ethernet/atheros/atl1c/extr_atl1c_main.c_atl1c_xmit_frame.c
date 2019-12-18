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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct atl1c_tpd_desc {int word1; int /*<<< orphan*/  vlan_tag; } ;
struct atl1c_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  enum atl1c_trans_queue { ____Placeholder_atl1c_trans_queue } atl1c_trans_queue ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  AT_VLAN_TO_TAG (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int TPD_ETH_TYPE_SHIFT ; 
 int TPD_INS_VTAG_SHIFT ; 
 int /*<<< orphan*/  __AT_DOWN ; 
 scalar_t__ atl1c_cal_tpd_req (struct sk_buff*) ; 
 struct atl1c_tpd_desc* atl1c_get_tpd (struct atl1c_adapter*,int) ; 
 scalar_t__ atl1c_tpd_avail (struct atl1c_adapter*,int) ; 
 int atl1c_trans_normal ; 
 scalar_t__ atl1c_tso_csum (struct atl1c_adapter*,struct sk_buff*,struct atl1c_tpd_desc**,int) ; 
 scalar_t__ atl1c_tx_map (struct atl1c_adapter*,struct sk_buff*,struct atl1c_tpd_desc*,int) ; 
 int /*<<< orphan*/  atl1c_tx_queue (struct atl1c_adapter*,struct sk_buff*,struct atl1c_tpd_desc*,int) ; 
 int /*<<< orphan*/  atl1c_tx_rollback (struct atl1c_adapter*,struct atl1c_tpd_desc*,int) ; 
 scalar_t__ cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct atl1c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_done ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t atl1c_xmit_frame(struct sk_buff *skb,
					  struct net_device *netdev)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);
	u16 tpd_req;
	struct atl1c_tpd_desc *tpd;
	enum atl1c_trans_queue type = atl1c_trans_normal;

	if (test_bit(__AT_DOWN, &adapter->flags)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	tpd_req = atl1c_cal_tpd_req(skb);

	if (atl1c_tpd_avail(adapter, type) < tpd_req) {
		/* no enough descriptor, just stop queue */
		netif_stop_queue(netdev);
		return NETDEV_TX_BUSY;
	}

	tpd = atl1c_get_tpd(adapter, type);

	/* do TSO and check sum */
	if (atl1c_tso_csum(adapter, skb, &tpd, type) != 0) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (unlikely(skb_vlan_tag_present(skb))) {
		u16 vlan = skb_vlan_tag_get(skb);
		__le16 tag;

		vlan = cpu_to_le16(vlan);
		AT_VLAN_TO_TAG(vlan, tag);
		tpd->word1 |= 1 << TPD_INS_VTAG_SHIFT;
		tpd->vlan_tag = tag;
	}

	if (skb_network_offset(skb) != ETH_HLEN)
		tpd->word1 |= 1 << TPD_ETH_TYPE_SHIFT; /* Ethernet frame */

	if (atl1c_tx_map(adapter, skb, tpd, type) < 0) {
		netif_info(adapter, tx_done, adapter->netdev,
			   "tx-skb dropped due to dma error\n");
		/* roll back tpd/buffer */
		atl1c_tx_rollback(adapter, tpd, type);
		dev_kfree_skb_any(skb);
	} else {
		netdev_sent_queue(adapter->netdev, skb->len);
		atl1c_tx_queue(adapter, skb, tpd, type);
	}

	return NETDEV_TX_OK;
}