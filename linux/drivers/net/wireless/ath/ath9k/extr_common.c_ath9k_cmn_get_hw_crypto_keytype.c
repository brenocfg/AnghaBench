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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_1__* hw_key; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct TYPE_3__ {int cipher; } ;

/* Variables and functions */
 int ATH9K_KEY_TYPE_AES ; 
 int ATH9K_KEY_TYPE_CLEAR ; 
 int ATH9K_KEY_TYPE_TKIP ; 
 int ATH9K_KEY_TYPE_WEP ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 

int ath9k_cmn_get_hw_crypto_keytype(struct sk_buff *skb)
{
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	if (tx_info->control.hw_key) {
		switch (tx_info->control.hw_key->cipher) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			return ATH9K_KEY_TYPE_WEP;
		case WLAN_CIPHER_SUITE_TKIP:
			return ATH9K_KEY_TYPE_TKIP;
		case WLAN_CIPHER_SUITE_CCMP:
			return ATH9K_KEY_TYPE_AES;
		default:
			break;
		}
	}

	return ATH9K_KEY_TYPE_CLEAR;
}