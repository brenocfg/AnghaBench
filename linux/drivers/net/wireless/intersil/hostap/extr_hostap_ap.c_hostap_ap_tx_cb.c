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
struct sk_buff {int /*<<< orphan*/  cb; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; scalar_t__ dev; scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ap_data {TYPE_1__* local; } ;
struct TYPE_2__ {scalar_t__ apdev; int /*<<< orphan*/  hostapd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  IEEE80211_FCTL_VERS ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  hostap_80211_get_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostap_ap_tx_cb(struct sk_buff *skb, int ok, void *data)
{
	struct ap_data *ap = data;
	struct ieee80211_hdr *hdr;

	if (!ap->local->hostapd || !ap->local->apdev) {
		dev_kfree_skb(skb);
		return;
	}

	/* Pass the TX callback frame to the hostapd; use 802.11 header version
	 * 1 to indicate failure (no ACK) and 2 success (frame ACKed) */

	hdr = (struct ieee80211_hdr *) skb->data;
	hdr->frame_control &= cpu_to_le16(~IEEE80211_FCTL_VERS);
	hdr->frame_control |= cpu_to_le16(ok ? BIT(1) : BIT(0));

	skb->dev = ap->local->apdev;
	skb_pull(skb, hostap_80211_get_hdrlen(hdr->frame_control));
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = cpu_to_be16(ETH_P_802_2);
	memset(skb->cb, 0, sizeof(skb->cb));
	netif_rx(skb);
}