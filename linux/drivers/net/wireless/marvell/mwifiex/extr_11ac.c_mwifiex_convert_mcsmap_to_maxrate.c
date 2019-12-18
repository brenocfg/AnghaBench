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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int /*<<< orphan*/  usr_dot_11ac_dev_cap_bg; int /*<<< orphan*/  usr_dot_11ac_dev_cap_a; } ;

/* Variables and functions */
 int BAND_AAC ; 
 scalar_t__ GET_VHTCAP_CHWDSET (int /*<<< orphan*/ ) ; 
 int GET_VHTNSSMCS (scalar_t__,int) ; 
 int IEEE80211_VHT_MCS_NOT_SUPPORTED ; 
 int IEEE80211_VHT_MCS_SUPPORT_0_9 ; 
 scalar_t__** max_rate_lgi_160MHZ ; 
 scalar_t__** max_rate_lgi_80MHZ ; 

__attribute__((used)) static u16
mwifiex_convert_mcsmap_to_maxrate(struct mwifiex_private *priv,
				  u8 bands, u16 mcs_map)
{
	u8 i, nss, mcs;
	u16 max_rate = 0;
	u32 usr_vht_cap_info = 0;
	struct mwifiex_adapter *adapter = priv->adapter;

	if (bands & BAND_AAC)
		usr_vht_cap_info = adapter->usr_dot_11ac_dev_cap_a;
	else
		usr_vht_cap_info = adapter->usr_dot_11ac_dev_cap_bg;

	/* find the max NSS supported */
	nss = 1;
	for (i = 1; i <= 8; i++) {
		mcs = GET_VHTNSSMCS(mcs_map, i);
		if (mcs < IEEE80211_VHT_MCS_NOT_SUPPORTED)
			nss = i;
	}
	mcs = GET_VHTNSSMCS(mcs_map, nss);

	/* if mcs is 3, nss must be 1 (NSS = 1). Default mcs to MCS 0~9 */
	if (mcs == IEEE80211_VHT_MCS_NOT_SUPPORTED)
		mcs = IEEE80211_VHT_MCS_SUPPORT_0_9;

	if (GET_VHTCAP_CHWDSET(usr_vht_cap_info)) {
		/* support 160 MHz */
		max_rate = max_rate_lgi_160MHZ[nss - 1][mcs];
		if (!max_rate)
			/* MCS9 is not supported in NSS6 */
			max_rate = max_rate_lgi_160MHZ[nss - 1][mcs - 1];
	} else {
		max_rate = max_rate_lgi_80MHZ[nss - 1][mcs];
		if (!max_rate)
			/* MCS9 is not supported in NSS3 */
			max_rate = max_rate_lgi_80MHZ[nss - 1][mcs - 1];
	}

	return max_rate;
}