#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct il_rx_buf {int /*<<< orphan*/ * page; } ;
struct TYPE_6__ {int rx_page_order; } ;
struct il_priv {int /*<<< orphan*/  hw; int /*<<< orphan*/  alloc_rxb_page; TYPE_3__ hw_params; TYPE_2__* cfg; int /*<<< orphan*/  stop_reason; int /*<<< orphan*/  is_open; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {TYPE_1__* mod_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  sw_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_DROP (char*) ; 
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  IL_STOP_REASON_PASSIVE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SMALL_PACKET_SIZE ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ il_set_decrypted_flag (struct il_priv*,struct ieee80211_hdr*,int /*<<< orphan*/ ,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  il_update_stats (struct il_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_wake_queues_by_reason (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 int rxb_addr (struct il_rx_buf*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,struct ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
il4965_pass_packet_to_mac80211(struct il_priv *il, struct ieee80211_hdr *hdr,
			       u32 len, u32 ampdu_status, struct il_rx_buf *rxb,
			       struct ieee80211_rx_status *stats)
{
	struct sk_buff *skb;
	__le16 fc = hdr->frame_control;

	/* We only process data packets if the interface is open */
	if (unlikely(!il->is_open)) {
		D_DROP("Dropping packet while interface is not open.\n");
		return;
	}

	if (unlikely(test_bit(IL_STOP_REASON_PASSIVE, &il->stop_reason))) {
		il_wake_queues_by_reason(il, IL_STOP_REASON_PASSIVE);
		D_INFO("Woke queues - frame received on passive channel\n");
	}

	/* In case of HW accelerated crypto and bad decryption, drop */
	if (!il->cfg->mod_params->sw_crypto &&
	    il_set_decrypted_flag(il, hdr, ampdu_status, stats))
		return;

	skb = dev_alloc_skb(SMALL_PACKET_SIZE);
	if (!skb) {
		IL_ERR("dev_alloc_skb failed\n");
		return;
	}

	if (len <= SMALL_PACKET_SIZE) {
		skb_put_data(skb, hdr, len);
	} else {
		skb_add_rx_frag(skb, 0, rxb->page, (void *)hdr - rxb_addr(rxb),
				len, PAGE_SIZE << il->hw_params.rx_page_order);
		il->alloc_rxb_page--;
		rxb->page = NULL;
	}

	il_update_stats(il, false, fc, len);
	memcpy(IEEE80211_SKB_RXCB(skb), stats, sizeof(*stats));

	ieee80211_rx(il->hw, skb);
}