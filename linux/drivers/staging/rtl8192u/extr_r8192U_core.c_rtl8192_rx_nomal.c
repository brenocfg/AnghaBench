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
typedef  int u32 ;
struct sk_buff {int len; scalar_t__ data; scalar_t__ cb; } ;
struct rx_desc_819x_usb {int dummy; } ;
struct rtl_80211_hdr_1addr {int /*<<< orphan*/  addr1; } ;
struct rtl8192_rx_info {struct net_device* dev; } ;
struct TYPE_2__ {int rxbytesunicast; int /*<<< orphan*/  rxurberr; int /*<<< orphan*/  rxoktotal; } ;
struct r8192_priv {TYPE_1__ stats; int /*<<< orphan*/  ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_rx_stats {int noise; int /*<<< orphan*/  freq; int /*<<< orphan*/  rate; int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_24GHZ_BAND ; 
 int RX_URB_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_rx (int /*<<< orphan*/ ,struct sk_buff*,struct ieee80211_rx_stats*) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  query_rxdesc_status (struct sk_buff*,struct ieee80211_rx_stats*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static void rtl8192_rx_nomal(struct sk_buff *skb)
{
	struct rtl8192_rx_info *info = (struct rtl8192_rx_info *)skb->cb;
	struct net_device *dev = info->dev;
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	struct ieee80211_rx_stats stats = {
		.signal = 0,
		.noise = 0x100 - 98,
		.rate = 0,
		.freq = IEEE80211_24GHZ_BAND,
	};
	u32 rx_pkt_len = 0;
	struct rtl_80211_hdr_1addr *ieee80211_hdr = NULL;
	bool unicast_packet = false;

	/* 20 is for ps-poll */
	if ((skb->len >= (20 + sizeof(struct rx_desc_819x_usb))) && (skb->len < RX_URB_SIZE)) {
		/* first packet should not contain Rx aggregation header */
		query_rxdesc_status(skb, &stats, false);
		/* TODO */
		/* hardware related info */
		/* Process the MPDU received */
		skb_trim(skb, skb->len - 4/*sCrcLng*/);

		rx_pkt_len = skb->len;
		ieee80211_hdr = (struct rtl_80211_hdr_1addr *)skb->data;
		unicast_packet = false;
		if (is_broadcast_ether_addr(ieee80211_hdr->addr1)) {
			/* TODO */
		} else if (is_multicast_ether_addr(ieee80211_hdr->addr1)) {
			/* TODO */
		} else {
			/* unicast packet */
			unicast_packet = true;
		}

		if (!ieee80211_rx(priv->ieee80211, skb, &stats)) {
			dev_kfree_skb_any(skb);
		} else {
			priv->stats.rxoktotal++;
			if (unicast_packet)
				priv->stats.rxbytesunicast += rx_pkt_len;
		}
	} else {
		priv->stats.rxurberr++;
		netdev_dbg(dev, "actual_length: %d\n", skb->len);
		dev_kfree_skb_any(skb);
	}
}