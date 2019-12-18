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
struct cfg80211_chan_def {int /*<<< orphan*/  width; TYPE_1__* chan; } ;
typedef  enum wmi_phy_mode { ____Placeholder_wmi_phy_mode } wmi_phy_mode ;
struct TYPE_2__ {int band; int flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_NO_OFDM ; 
 int MODE_11A ; 
 int MODE_11AC_VHT160 ; 
 int MODE_11AC_VHT80 ; 
 int MODE_11AC_VHT80_80 ; 
 int MODE_11B ; 
 int MODE_11G ; 
 int MODE_11NA_HT20 ; 
 int MODE_11NA_HT40 ; 
 int MODE_11NG_HT20 ; 
 int MODE_11NG_HT40 ; 
 int MODE_UNKNOWN ; 
#define  NL80211_BAND_2GHZ 137 
#define  NL80211_BAND_5GHZ 136 
#define  NL80211_CHAN_WIDTH_10 135 
#define  NL80211_CHAN_WIDTH_160 134 
#define  NL80211_CHAN_WIDTH_20 133 
#define  NL80211_CHAN_WIDTH_20_NOHT 132 
#define  NL80211_CHAN_WIDTH_40 131 
#define  NL80211_CHAN_WIDTH_5 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline enum wmi_phy_mode
chan_to_phymode(const struct cfg80211_chan_def *chandef)
{
	enum wmi_phy_mode phymode = MODE_UNKNOWN;

	switch (chandef->chan->band) {
	case NL80211_BAND_2GHZ:
		switch (chandef->width) {
		case NL80211_CHAN_WIDTH_20_NOHT:
			if (chandef->chan->flags & IEEE80211_CHAN_NO_OFDM)
				phymode = MODE_11B;
			else
				phymode = MODE_11G;
			break;
		case NL80211_CHAN_WIDTH_20:
			phymode = MODE_11NG_HT20;
			break;
		case NL80211_CHAN_WIDTH_40:
			phymode = MODE_11NG_HT40;
			break;
		case NL80211_CHAN_WIDTH_5:
		case NL80211_CHAN_WIDTH_10:
		case NL80211_CHAN_WIDTH_80:
		case NL80211_CHAN_WIDTH_80P80:
		case NL80211_CHAN_WIDTH_160:
			phymode = MODE_UNKNOWN;
			break;
		}
		break;
	case NL80211_BAND_5GHZ:
		switch (chandef->width) {
		case NL80211_CHAN_WIDTH_20_NOHT:
			phymode = MODE_11A;
			break;
		case NL80211_CHAN_WIDTH_20:
			phymode = MODE_11NA_HT20;
			break;
		case NL80211_CHAN_WIDTH_40:
			phymode = MODE_11NA_HT40;
			break;
		case NL80211_CHAN_WIDTH_80:
			phymode = MODE_11AC_VHT80;
			break;
		case NL80211_CHAN_WIDTH_160:
			phymode = MODE_11AC_VHT160;
			break;
		case NL80211_CHAN_WIDTH_80P80:
			phymode = MODE_11AC_VHT80_80;
			break;
		case NL80211_CHAN_WIDTH_5:
		case NL80211_CHAN_WIDTH_10:
			phymode = MODE_UNKNOWN;
			break;
		}
		break;
	default:
		break;
	}

	WARN_ON(phymode == MODE_UNKNOWN);
	return phymode;
}