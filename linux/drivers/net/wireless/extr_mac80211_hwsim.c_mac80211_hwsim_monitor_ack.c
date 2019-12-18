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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  cb; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  dev; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; void* duration_id; void* frame_control; } ;
struct ieee80211_channel {int center_freq; } ;
struct TYPE_2__ {int /*<<< orphan*/  it_present; void* it_len; scalar_t__ it_pad; int /*<<< orphan*/  it_version; } ;
struct hwsim_radiotap_ack_hdr {void* rt_chbitmask; void* rt_channel; scalar_t__ pad; scalar_t__ rt_flags; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_FTYPE_CTL ; 
 int IEEE80211_RADIOTAP_CHANNEL ; 
 int IEEE80211_RADIOTAP_FLAGS ; 
 int IEEE80211_STYPE_ACK ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  PKTHDR_RADIOTAP_VERSION ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwsim_mon ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 void* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void mac80211_hwsim_monitor_ack(struct ieee80211_channel *chan,
				       const u8 *addr)
{
	struct sk_buff *skb;
	struct hwsim_radiotap_ack_hdr *hdr;
	u16 flags;
	struct ieee80211_hdr *hdr11;

	if (!netif_running(hwsim_mon))
		return;

	skb = dev_alloc_skb(100);
	if (skb == NULL)
		return;

	hdr = skb_put(skb, sizeof(*hdr));
	hdr->hdr.it_version = PKTHDR_RADIOTAP_VERSION;
	hdr->hdr.it_pad = 0;
	hdr->hdr.it_len = cpu_to_le16(sizeof(*hdr));
	hdr->hdr.it_present = cpu_to_le32((1 << IEEE80211_RADIOTAP_FLAGS) |
					  (1 << IEEE80211_RADIOTAP_CHANNEL));
	hdr->rt_flags = 0;
	hdr->pad = 0;
	hdr->rt_channel = cpu_to_le16(chan->center_freq);
	flags = IEEE80211_CHAN_2GHZ;
	hdr->rt_chbitmask = cpu_to_le16(flags);

	hdr11 = skb_put(skb, 10);
	hdr11->frame_control = cpu_to_le16(IEEE80211_FTYPE_CTL |
					   IEEE80211_STYPE_ACK);
	hdr11->duration_id = cpu_to_le16(0);
	memcpy(hdr11->addr1, addr, ETH_ALEN);

	skb->dev = hwsim_mon;
	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);
	memset(skb->cb, 0, sizeof(skb->cb));
	netif_rx(skb);
}