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
typedef  int u32 ;
struct TYPE_2__ {void* it_present; void* it_len; scalar_t__ it_version; } ;
struct wilc_wfi_radiotap_hdr {int rate; TYPE_1__ hdr; int /*<<< orphan*/  tx_flags; } ;
struct wilc_wfi_radiotap_cb_hdr {int rate; TYPE_1__ hdr; int /*<<< orphan*/  tx_flags; } ;
struct sk_buff {struct wilc_wfi_radiotap_hdr* cb; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  ip_summed; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int GET_PKT_OFFSET (int) ; 
 int HOST_HDR_OFFSET ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_F_TX_FAIL ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_F_TX_RTS ; 
 int IEEE80211_RADIOTAP_RATE ; 
 int IS_MANAGMEMENT_CALLBACK ; 
 int IS_MGMT_STATUS_SUCCES ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int TX_RADIOTAP_PRESENT ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wilc_wfi_radiotap_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 struct wilc_wfi_radiotap_hdr* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

void wilc_wfi_monitor_rx(struct net_device *mon_dev, u8 *buff, u32 size)
{
	u32 header, pkt_offset;
	struct sk_buff *skb = NULL;
	struct wilc_wfi_radiotap_hdr *hdr;
	struct wilc_wfi_radiotap_cb_hdr *cb_hdr;

	if (!mon_dev)
		return;

	if (!netif_running(mon_dev))
		return;

	/* Get WILC header */
	header = get_unaligned_le32(buff - HOST_HDR_OFFSET);
	/*
	 * The packet offset field contain info about what type of management
	 * the frame we are dealing with and ack status
	 */
	pkt_offset = GET_PKT_OFFSET(header);

	if (pkt_offset & IS_MANAGMEMENT_CALLBACK) {
		/* hostapd callback mgmt frame */

		skb = dev_alloc_skb(size + sizeof(*cb_hdr));
		if (!skb)
			return;

		skb_put_data(skb, buff, size);

		cb_hdr = skb_push(skb, sizeof(*cb_hdr));
		memset(cb_hdr, 0, sizeof(*cb_hdr));

		cb_hdr->hdr.it_version = 0; /* PKTHDR_RADIOTAP_VERSION; */

		cb_hdr->hdr.it_len = cpu_to_le16(sizeof(*cb_hdr));

		cb_hdr->hdr.it_present = cpu_to_le32(TX_RADIOTAP_PRESENT);

		cb_hdr->rate = 5;

		if (pkt_offset & IS_MGMT_STATUS_SUCCES)	{
			/* success */
			cb_hdr->tx_flags = IEEE80211_RADIOTAP_F_TX_RTS;
		} else {
			cb_hdr->tx_flags = IEEE80211_RADIOTAP_F_TX_FAIL;
		}

	} else {
		skb = dev_alloc_skb(size + sizeof(*hdr));

		if (!skb)
			return;

		skb_put_data(skb, buff, size);
		hdr = skb_push(skb, sizeof(*hdr));
		memset(hdr, 0, sizeof(struct wilc_wfi_radiotap_hdr));
		hdr->hdr.it_version = 0; /* PKTHDR_RADIOTAP_VERSION; */
		hdr->hdr.it_len = cpu_to_le16(sizeof(*hdr));
		hdr->hdr.it_present = cpu_to_le32
				(1 << IEEE80211_RADIOTAP_RATE);
		hdr->rate = 5;
	}

	skb->dev = mon_dev;
	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);
	memset(skb->cb, 0, sizeof(skb->cb));

	netif_rx(skb);
}