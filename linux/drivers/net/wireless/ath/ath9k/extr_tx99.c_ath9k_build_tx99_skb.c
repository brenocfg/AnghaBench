#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {struct ieee80211_tx_info* data; } ;
struct ieee80211_tx_rate {int count; int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {TYPE_6__* vif; struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {TYPE_5__ control; int /*<<< orphan*/  flags; int /*<<< orphan*/  band; } ;
struct ieee80211_hw {TYPE_1__* wiphy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; struct ieee80211_tx_info* addr3; struct ieee80211_tx_info* addr2; struct ieee80211_tx_info* addr1; scalar_t__ duration_id; int /*<<< orphan*/  frame_control; } ;
struct ath_vif {int /*<<< orphan*/  seq_no; } ;
struct ath_softc {TYPE_6__* tx99_vif; TYPE_4__* cur_chan; struct ath_hw* sc_ah; struct ieee80211_hw* hw; } ;
struct ath_hw {scalar_t__ curchan; } ;
struct TYPE_12__ {scalar_t__ drv_priv; } ;
struct TYPE_9__ {TYPE_2__* chan; } ;
struct TYPE_10__ {TYPE_3__ chandef; } ;
struct TYPE_8__ {int /*<<< orphan*/  band; } ;
struct TYPE_7__ {int* perm_addr; } ;
typedef  int /*<<< orphan*/  PN9Data ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_FTYPE_DATA ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_CTL_NO_ACK ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 scalar_t__ IS_CHAN_HT (scalar_t__) ; 
 scalar_t__ IS_CHAN_HT40 (scalar_t__) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_tx_info*,int*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_tx_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *ath9k_build_tx99_skb(struct ath_softc *sc)
{
	static u8 PN9Data[] = {0xff, 0x87, 0xb8, 0x59, 0xb7, 0xa1, 0xcc, 0x24,
			       0x57, 0x5e, 0x4b, 0x9c, 0x0e, 0xe9, 0xea, 0x50,
			       0x2a, 0xbe, 0xb4, 0x1b, 0xb6, 0xb0, 0x5d, 0xf1,
			       0xe6, 0x9a, 0xe3, 0x45, 0xfd, 0x2c, 0x53, 0x18,
			       0x0c, 0xca, 0xc9, 0xfb, 0x49, 0x37, 0xe5, 0xa8,
			       0x51, 0x3b, 0x2f, 0x61, 0xaa, 0x72, 0x18, 0x84,
			       0x02, 0x23, 0x23, 0xab, 0x63, 0x89, 0x51, 0xb3,
			       0xe7, 0x8b, 0x72, 0x90, 0x4c, 0xe8, 0xfb, 0xc0};
	u32 len = 1200;
	struct ieee80211_tx_rate *rate;
	struct ieee80211_hw *hw = sc->hw;
	struct ath_hw *ah = sc->sc_ah;
	struct ieee80211_hdr *hdr;
	struct ieee80211_tx_info *tx_info;
	struct sk_buff *skb;
	struct ath_vif *avp;

	skb = alloc_skb(len, GFP_KERNEL);
	if (!skb)
		return NULL;

	skb_put(skb, len);

	memset(skb->data, 0, len);

	hdr = (struct ieee80211_hdr *)skb->data;
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA);
	hdr->duration_id = 0;

	memcpy(hdr->addr1, hw->wiphy->perm_addr, ETH_ALEN);
	memcpy(hdr->addr2, hw->wiphy->perm_addr, ETH_ALEN);
	memcpy(hdr->addr3, hw->wiphy->perm_addr, ETH_ALEN);

	if (sc->tx99_vif) {
		avp = (struct ath_vif *) sc->tx99_vif->drv_priv;
		hdr->seq_ctrl |= cpu_to_le16(avp->seq_no);
	}

	tx_info = IEEE80211_SKB_CB(skb);
	memset(tx_info, 0, sizeof(*tx_info));
	rate = &tx_info->control.rates[0];
	tx_info->band = sc->cur_chan->chandef.chan->band;
	tx_info->flags = IEEE80211_TX_CTL_NO_ACK;
	tx_info->control.vif = sc->tx99_vif;
	rate->count = 1;
	if (ah->curchan && IS_CHAN_HT(ah->curchan)) {
		rate->flags |= IEEE80211_TX_RC_MCS;
		if (IS_CHAN_HT40(ah->curchan))
			rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
	}

	memcpy(skb->data + sizeof(*hdr), PN9Data, sizeof(PN9Data));

	return skb;
}