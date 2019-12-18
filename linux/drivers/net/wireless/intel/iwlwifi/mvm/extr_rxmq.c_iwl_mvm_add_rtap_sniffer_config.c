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
struct sk_buff {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  cur_aid; } ;
struct ieee80211_vendor_radiotap {int align; int* oui; int subns; int present; int len; int pad; scalar_t__ data; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int const) ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  RX_FLAG_RADIOTAP_VENDOR_DATA ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct ieee80211_vendor_radiotap* skb_put (struct sk_buff*,int const) ; 

__attribute__((used)) static void iwl_mvm_add_rtap_sniffer_config(struct iwl_mvm *mvm,
					    struct sk_buff *skb)
{
	struct ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_vendor_radiotap *radiotap;
	const int size = sizeof(*radiotap) + sizeof(__le16);

	if (!mvm->cur_aid)
		return;

	/* ensure alignment */
	BUILD_BUG_ON((size + 2) % 4);

	radiotap = skb_put(skb, size + 2);
	radiotap->align = 1;
	/* Intel OUI */
	radiotap->oui[0] = 0xf6;
	radiotap->oui[1] = 0x54;
	radiotap->oui[2] = 0x25;
	/* radiotap sniffer config sub-namespace */
	radiotap->subns = 1;
	radiotap->present = 0x1;
	radiotap->len = size - sizeof(*radiotap);
	radiotap->pad = 2;

	/* fill the data now */
	memcpy(radiotap->data, &mvm->cur_aid, sizeof(mvm->cur_aid));
	/* and clear the padding */
	memset(radiotap->data + sizeof(__le16), 0, radiotap->pad);

	rx_status->flag |= RX_FLAG_RADIOTAP_VENDOR_DATA;
}