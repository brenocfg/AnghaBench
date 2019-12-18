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
typedef  int /*<<< orphan*/  vht_cap ;
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  band; } ;
struct mwifiex_private {TYPE_1__ curr_bss_params; } ;
struct ieee80211_vht_cap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_VHT_CAPABILITY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_vht_cap*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_vht_cap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_fill_vht_cap_tlv (struct mwifiex_private*,struct ieee80211_vht_cap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int mwifiex_tdls_add_vht_capab(struct mwifiex_private *priv,
				      struct sk_buff *skb)
{
	struct ieee80211_vht_cap vht_cap;
	u8 *pos;

	pos = skb_put(skb, sizeof(struct ieee80211_vht_cap) + 2);
	*pos++ = WLAN_EID_VHT_CAPABILITY;
	*pos++ = sizeof(struct ieee80211_vht_cap);

	memset(&vht_cap, 0, sizeof(struct ieee80211_vht_cap));

	mwifiex_fill_vht_cap_tlv(priv, &vht_cap, priv->curr_bss_params.band);
	memcpy(pos, &vht_cap, sizeof(vht_cap));

	return 0;
}