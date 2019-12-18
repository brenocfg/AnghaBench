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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct il_rx_pkt {int dummy; } ;
struct il_rx_buf {int /*<<< orphan*/ * page; } ;
struct TYPE_3__ {scalar_t__ rx_page_order; } ;
struct il_priv {int /*<<< orphan*/  hw; int /*<<< orphan*/  alloc_rxb_page; int /*<<< orphan*/  stop_reason; int /*<<< orphan*/  is_open; TYPE_1__ hw_params; } ;
struct il3945_rx_frame_hdr {scalar_t__ payload; int /*<<< orphan*/  len; } ;
struct il3945_rx_frame_end {int /*<<< orphan*/  status; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int /*<<< orphan*/  sw_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_DROP (char*) ; 
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 scalar_t__ IL39_RX_FRAME_SIZE ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 scalar_t__ IL_RX_DATA (struct il_rx_pkt*) ; 
 struct il3945_rx_frame_end* IL_RX_END (struct il_rx_pkt*) ; 
 struct il3945_rx_frame_hdr* IL_RX_HDR (struct il_rx_pkt*) ; 
 int /*<<< orphan*/  IL_STOP_REASON_PASSIVE ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ SMALL_PACKET_SIZE ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_rx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 TYPE_2__ il3945_mod_params ; 
 int /*<<< orphan*/  il_set_decrypted_flag (struct il_priv*,struct ieee80211_hdr*,int /*<<< orphan*/ ,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  il_update_stats (struct il_priv*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  il_wake_queues_by_reason (struct il_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,scalar_t__,scalar_t__) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
il3945_pass_packet_to_mac80211(struct il_priv *il, struct il_rx_buf *rxb,
			       struct ieee80211_rx_status *stats)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)IL_RX_DATA(pkt);
	struct il3945_rx_frame_hdr *rx_hdr = IL_RX_HDR(pkt);
	struct il3945_rx_frame_end *rx_end = IL_RX_END(pkt);
	u32 len = le16_to_cpu(rx_hdr->len);
	struct sk_buff *skb;
	__le16 fc = hdr->frame_control;
	u32 fraglen = PAGE_SIZE << il->hw_params.rx_page_order;

	/* We received data from the HW, so stop the watchdog */
	if (unlikely(len + IL39_RX_FRAME_SIZE > fraglen)) {
		D_DROP("Corruption detected!\n");
		return;
	}

	/* We only process data packets if the interface is open */
	if (unlikely(!il->is_open)) {
		D_DROP("Dropping packet while interface is not open.\n");
		return;
	}

	if (unlikely(test_bit(IL_STOP_REASON_PASSIVE, &il->stop_reason))) {
		il_wake_queues_by_reason(il, IL_STOP_REASON_PASSIVE);
		D_INFO("Woke queues - frame received on passive channel\n");
	}

	skb = dev_alloc_skb(SMALL_PACKET_SIZE);
	if (!skb) {
		IL_ERR("dev_alloc_skb failed\n");
		return;
	}

	if (!il3945_mod_params.sw_crypto)
		il_set_decrypted_flag(il, (struct ieee80211_hdr *)pkt,
				      le32_to_cpu(rx_end->status), stats);

	/* If frame is small enough to fit into skb->head, copy it
	 * and do not consume a full page
	 */
	if (len <= SMALL_PACKET_SIZE) {
		skb_put_data(skb, rx_hdr->payload, len);
	} else {
		skb_add_rx_frag(skb, 0, rxb->page,
				(void *)rx_hdr->payload - (void *)pkt, len,
				fraglen);
		il->alloc_rxb_page--;
		rxb->page = NULL;
	}
	il_update_stats(il, false, fc, len);
	memcpy(IEEE80211_SKB_RXCB(skb), stats, sizeof(*stats));

	ieee80211_rx(il->hw, skb);
}