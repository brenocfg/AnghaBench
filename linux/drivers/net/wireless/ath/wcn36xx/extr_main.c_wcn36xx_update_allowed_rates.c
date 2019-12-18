#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_10__ {int /*<<< orphan*/  supported_mcs_set; int /*<<< orphan*/ * ofdm_rates; int /*<<< orphan*/ * dsss_rates; int /*<<< orphan*/  op_rate_mode; } ;
struct wcn36xx_sta {TYPE_5__ supported_rates; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_mask; } ;
struct TYPE_7__ {TYPE_1__ mcs; scalar_t__ ht_supported; } ;
struct ieee80211_sta {int* supp_rates; TYPE_2__ ht_cap; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_9__ {int /*<<< orphan*/  hw_value; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  STA_11n ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 struct wcn36xx_sta* wcn36xx_sta_to_priv (struct ieee80211_sta*) ; 
 TYPE_4__* wcn_2ghz_rates ; 
 TYPE_3__* wcn_5ghz_rates ; 

__attribute__((used)) static void wcn36xx_update_allowed_rates(struct ieee80211_sta *sta,
					 enum nl80211_band band)
{
	int i, size;
	u16 *rates_table;
	struct wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(sta);
	u32 rates = sta->supp_rates[band];

	memset(&sta_priv->supported_rates, 0,
		sizeof(sta_priv->supported_rates));
	sta_priv->supported_rates.op_rate_mode = STA_11n;

	size = ARRAY_SIZE(sta_priv->supported_rates.dsss_rates);
	rates_table = sta_priv->supported_rates.dsss_rates;
	if (band == NL80211_BAND_2GHZ) {
		for (i = 0; i < size; i++) {
			if (rates & 0x01) {
				rates_table[i] = wcn_2ghz_rates[i].hw_value;
				rates = rates >> 1;
			}
		}
	}

	size = ARRAY_SIZE(sta_priv->supported_rates.ofdm_rates);
	rates_table = sta_priv->supported_rates.ofdm_rates;
	for (i = 0; i < size; i++) {
		if (rates & 0x01) {
			rates_table[i] = wcn_5ghz_rates[i].hw_value;
			rates = rates >> 1;
		}
	}

	if (sta->ht_cap.ht_supported) {
		BUILD_BUG_ON(sizeof(sta->ht_cap.mcs.rx_mask) >
			sizeof(sta_priv->supported_rates.supported_mcs_set));
		memcpy(sta_priv->supported_rates.supported_mcs_set,
		       sta->ht_cap.mcs.rx_mask,
		       sizeof(sta->ht_cap.mcs.rx_mask));
	}
}