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
typedef  int u16 ;
struct tx_packet_desc {int word3; int word2; } ;
struct sk_buff {scalar_t__ len; scalar_t__ protocol; } ;
struct net_device {int dummy; } ;
struct atl1_tpd_ring {int /*<<< orphan*/  next_to_use; } ;
struct atl1_adapter {TYPE_1__* pdev; struct atl1_tpd_ring tpd_ring; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {unsigned int nr_frags; unsigned int gso_size; int /*<<< orphan*/ * frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ATL1_MAX_TX_BUF_LEN ; 
 struct tx_packet_desc* ATL1_TPD_DESC (struct atl1_tpd_ring*,int) ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int TPD_INS_VL_TAG_SHIFT ; 
 int TPD_VLANTAG_MASK ; 
 int TPD_VLANTAG_SHIFT ; 
 int atl1_tpd_avail (struct atl1_tpd_ring*) ; 
 int atl1_tso (struct atl1_adapter*,struct sk_buff*,struct tx_packet_desc*) ; 
 int atl1_tx_csum (struct atl1_adapter*,struct sk_buff*,struct tx_packet_desc*) ; 
 int /*<<< orphan*/  atl1_tx_map (struct atl1_adapter*,struct sk_buff*,struct tx_packet_desc*) ; 
 int /*<<< orphan*/  atl1_tx_queue (struct atl1_adapter*,int,struct tx_packet_desc*) ; 
 int /*<<< orphan*/  atl1_update_mailbox (struct atl1_adapter*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tx_packet_desc*,int /*<<< orphan*/ ,int) ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_queued (struct atl1_adapter*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 unsigned int tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t atl1_xmit_frame(struct sk_buff *skb,
					 struct net_device *netdev)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);
	struct atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	int len;
	int tso;
	int count = 1;
	int ret_val;
	struct tx_packet_desc *ptpd;
	u16 vlan_tag;
	unsigned int nr_frags = 0;
	unsigned int mss = 0;
	unsigned int f;
	unsigned int proto_hdr_len;

	len = skb_headlen(skb);

	if (unlikely(skb->len <= 0)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	nr_frags = skb_shinfo(skb)->nr_frags;
	for (f = 0; f < nr_frags; f++) {
		unsigned int f_size = skb_frag_size(&skb_shinfo(skb)->frags[f]);
		count += (f_size + ATL1_MAX_TX_BUF_LEN - 1) /
			 ATL1_MAX_TX_BUF_LEN;
	}

	mss = skb_shinfo(skb)->gso_size;
	if (mss) {
		if (skb->protocol == htons(ETH_P_IP)) {
			proto_hdr_len = (skb_transport_offset(skb) +
					 tcp_hdrlen(skb));
			if (unlikely(proto_hdr_len > len)) {
				dev_kfree_skb_any(skb);
				return NETDEV_TX_OK;
			}
			/* need additional TPD ? */
			if (proto_hdr_len != len)
				count += (len - proto_hdr_len +
					ATL1_MAX_TX_BUF_LEN - 1) /
					ATL1_MAX_TX_BUF_LEN;
		}
	}

	if (atl1_tpd_avail(&adapter->tpd_ring) < count) {
		/* not enough descriptors */
		netif_stop_queue(netdev);
		if (netif_msg_tx_queued(adapter))
			dev_printk(KERN_DEBUG, &adapter->pdev->dev,
				"tx busy\n");
		return NETDEV_TX_BUSY;
	}

	ptpd = ATL1_TPD_DESC(tpd_ring,
		(u16) atomic_read(&tpd_ring->next_to_use));
	memset(ptpd, 0, sizeof(struct tx_packet_desc));

	if (skb_vlan_tag_present(skb)) {
		vlan_tag = skb_vlan_tag_get(skb);
		vlan_tag = (vlan_tag << 4) | (vlan_tag >> 13) |
			((vlan_tag >> 9) & 0x8);
		ptpd->word3 |= 1 << TPD_INS_VL_TAG_SHIFT;
		ptpd->word2 |= (vlan_tag & TPD_VLANTAG_MASK) <<
			TPD_VLANTAG_SHIFT;
	}

	tso = atl1_tso(adapter, skb, ptpd);
	if (tso < 0) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (!tso) {
		ret_val = atl1_tx_csum(adapter, skb, ptpd);
		if (ret_val < 0) {
			dev_kfree_skb_any(skb);
			return NETDEV_TX_OK;
		}
	}

	atl1_tx_map(adapter, skb, ptpd);
	atl1_tx_queue(adapter, count, ptpd);
	atl1_update_mailbox(adapter);
	return NETDEV_TX_OK;
}