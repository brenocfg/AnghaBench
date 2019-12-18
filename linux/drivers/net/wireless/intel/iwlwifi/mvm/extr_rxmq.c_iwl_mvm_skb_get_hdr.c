#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void u8 ;
struct sk_buff {void* data; } ;
struct ieee80211_vendor_radiotap {scalar_t__ pad; scalar_t__ len; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_radiotap_lsig {int dummy; } ;
struct ieee80211_radiotap_he_mu {int dummy; } ;
struct ieee80211_radiotap_he {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int RX_FLAG_RADIOTAP_HE ; 
 int RX_FLAG_RADIOTAP_HE_MU ; 
 int RX_FLAG_RADIOTAP_LSIG ; 
 int RX_FLAG_RADIOTAP_VENDOR_DATA ; 

__attribute__((used)) static void *iwl_mvm_skb_get_hdr(struct sk_buff *skb)
{
	struct ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	u8 *data = skb->data;

	/* Alignment concerns */
	BUILD_BUG_ON(sizeof(struct ieee80211_radiotap_he) % 4);
	BUILD_BUG_ON(sizeof(struct ieee80211_radiotap_he_mu) % 4);
	BUILD_BUG_ON(sizeof(struct ieee80211_radiotap_lsig) % 4);
	BUILD_BUG_ON(sizeof(struct ieee80211_vendor_radiotap) % 4);

	if (rx_status->flag & RX_FLAG_RADIOTAP_HE)
		data += sizeof(struct ieee80211_radiotap_he);
	if (rx_status->flag & RX_FLAG_RADIOTAP_HE_MU)
		data += sizeof(struct ieee80211_radiotap_he_mu);
	if (rx_status->flag & RX_FLAG_RADIOTAP_LSIG)
		data += sizeof(struct ieee80211_radiotap_lsig);
	if (rx_status->flag & RX_FLAG_RADIOTAP_VENDOR_DATA) {
		struct ieee80211_vendor_radiotap *radiotap = (void *)data;

		data += sizeof(*radiotap) + radiotap->len + radiotap->pad;
	}

	return data;
}