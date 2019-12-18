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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_10__ {scalar_t__* rx_mask; } ;
struct TYPE_11__ {TYPE_4__ mcs; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_mcs_map; } ;
struct TYPE_9__ {TYPE_2__ vht_mcs; } ;
struct ieee80211_supported_band {TYPE_5__ ht_cap; TYPE_3__ vht_cap; } ;
struct cfg80211_bitrate_mask {TYPE_6__* control; } ;
struct TYPE_7__ {struct ieee80211_supported_band* sbands; } ;
struct ath10k {TYPE_1__ mac; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_12__ {scalar_t__* ht_mcs; scalar_t__* vht_mcs; scalar_t__ legacy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int BIT (int) ; 
 scalar_t__ ath10k_mac_get_max_vht_mcs_map (int /*<<< orphan*/ ,int) ; 
 int fls (int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ath10k_mac_bitrate_mask_get_single_nss(struct ath10k *ar,
				       enum nl80211_band band,
				       const struct cfg80211_bitrate_mask *mask,
				       int *nss)
{
	struct ieee80211_supported_band *sband = &ar->mac.sbands[band];
	u16 vht_mcs_map = le16_to_cpu(sband->vht_cap.vht_mcs.tx_mcs_map);
	u8 ht_nss_mask = 0;
	u8 vht_nss_mask = 0;
	int i;

	if (mask->control[band].legacy)
		return false;

	for (i = 0; i < ARRAY_SIZE(mask->control[band].ht_mcs); i++) {
		if (mask->control[band].ht_mcs[i] == 0)
			continue;
		else if (mask->control[band].ht_mcs[i] ==
			 sband->ht_cap.mcs.rx_mask[i])
			ht_nss_mask |= BIT(i);
		else
			return false;
	}

	for (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) {
		if (mask->control[band].vht_mcs[i] == 0)
			continue;
		else if (mask->control[band].vht_mcs[i] ==
			 ath10k_mac_get_max_vht_mcs_map(vht_mcs_map, i))
			vht_nss_mask |= BIT(i);
		else
			return false;
	}

	if (ht_nss_mask != vht_nss_mask)
		return false;

	if (ht_nss_mask == 0)
		return false;

	if (BIT(fls(ht_nss_mask)) - 1 != ht_nss_mask)
		return false;

	*nss = fls(ht_nss_mask);

	return true;
}