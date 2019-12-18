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
typedef  int /*<<< orphan*/  u32 ;
struct ath_regulatory {scalar_t__ country_code; int region; TYPE_1__* regpair; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {int /*<<< orphan*/  reg_5ghz_ctl; int /*<<< orphan*/  reg_2ghz_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_ETSI ; 
 int /*<<< orphan*/  CTL_FCC ; 
 int /*<<< orphan*/  CTL_MKK ; 
 scalar_t__ CTRY_DEFAULT ; 
#define  NL80211_BAND_2GHZ 132 
#define  NL80211_BAND_5GHZ 131 
#define  NL80211_DFS_ETSI 130 
#define  NL80211_DFS_FCC 129 
#define  NL80211_DFS_JP 128 
 int /*<<< orphan*/  NO_CTL ; 
 int /*<<< orphan*/  SD_NO_CTL ; 
 scalar_t__ ath_regd_get_eepromRD (struct ath_regulatory*) ; 
 scalar_t__ is_wwr_sku (scalar_t__) ; 

u32 ath_regd_get_band_ctl(struct ath_regulatory *reg,
			  enum nl80211_band band)
{
	if (!reg->regpair ||
	    (reg->country_code == CTRY_DEFAULT &&
	     is_wwr_sku(ath_regd_get_eepromRD(reg)))) {
		return SD_NO_CTL;
	}

	if (ath_regd_get_eepromRD(reg) == CTRY_DEFAULT) {
		switch (reg->region) {
		case NL80211_DFS_FCC:
			return CTL_FCC;
		case NL80211_DFS_ETSI:
			return CTL_ETSI;
		case NL80211_DFS_JP:
			return CTL_MKK;
		default:
			break;
		}
	}

	switch (band) {
	case NL80211_BAND_2GHZ:
		return reg->regpair->reg_2ghz_ctl;
	case NL80211_BAND_5GHZ:
		return reg->regpair->reg_5ghz_ctl;
	default:
		return NO_CTL;
	}
}