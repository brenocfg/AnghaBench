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
struct sk_buff {scalar_t__ data; } ;
struct mwl8k_priv {int dummy; } ;
struct TYPE_2__ {struct ieee80211_key_conf* hw_key; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_key_conf {int iv_len; int cipher; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_add_dma_header (struct mwl8k_priv*,struct sk_buff*,int,int) ; 

__attribute__((used)) static void mwl8k_encapsulate_tx_frame(struct mwl8k_priv *priv,
		struct sk_buff *skb)
{
	struct ieee80211_hdr *wh;
	struct ieee80211_tx_info *tx_info;
	struct ieee80211_key_conf *key_conf;
	int data_pad;
	int head_pad = 0;

	wh = (struct ieee80211_hdr *)skb->data;

	tx_info = IEEE80211_SKB_CB(skb);

	key_conf = NULL;
	if (ieee80211_is_data(wh->frame_control))
		key_conf = tx_info->control.hw_key;

	/*
	 * Make sure the packet header is in the DMA header format (4-address
	 * without QoS), and add head & tail padding when HW crypto is enabled.
	 *
	 * We have the following trailer padding requirements:
	 * - WEP: 4 trailer bytes (ICV)
	 * - TKIP: 12 trailer bytes (8 MIC + 4 ICV)
	 * - CCMP: 8 trailer bytes (MIC)
	 */
	data_pad = 0;
	if (key_conf != NULL) {
		head_pad = key_conf->iv_len;
		switch (key_conf->cipher) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			data_pad = 4;
			break;
		case WLAN_CIPHER_SUITE_TKIP:
			data_pad = 12;
			break;
		case WLAN_CIPHER_SUITE_CCMP:
			data_pad = 8;
			break;
		}
	}
	mwl8k_add_dma_header(priv, skb, head_pad, data_pad);
}