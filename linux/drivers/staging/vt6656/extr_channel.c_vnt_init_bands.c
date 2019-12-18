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
struct vnt_private {int rf_type; TYPE_2__* hw; } ;
struct ieee80211_channel {void* flags; void* max_power; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** bands; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ieee80211_channel*) ; 
 void* IEEE80211_CHAN_NO_HT40 ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
#define  RF_AIROHA7230 133 
#define  RF_AL2230 132 
#define  RF_AL2230S 131 
#define  RF_VT3226 130 
#define  RF_VT3226D0 129 
#define  RF_VT3342A0 128 
 void* VNT_RF_MAX_POWER ; 
 struct ieee80211_channel* vnt_channels_2ghz ; 
 struct ieee80211_channel* vnt_channels_5ghz ; 
 int /*<<< orphan*/  vnt_supported_2ghz_band ; 
 int /*<<< orphan*/  vnt_supported_5ghz_band ; 

void vnt_init_bands(struct vnt_private *priv)
{
	struct ieee80211_channel *ch;
	int i;

	switch (priv->rf_type) {
	case RF_AIROHA7230:
	case RF_VT3342A0:
	default:
		ch = vnt_channels_5ghz;

		for (i = 0; i < ARRAY_SIZE(vnt_channels_5ghz); i++) {
			ch[i].max_power = VNT_RF_MAX_POWER;
			ch[i].flags = IEEE80211_CHAN_NO_HT40;
		}

		priv->hw->wiphy->bands[NL80211_BAND_5GHZ] =
						&vnt_supported_5ghz_band;
	/* fallthrough */
	case RF_AL2230:
	case RF_AL2230S:
	case RF_VT3226:
	case RF_VT3226D0:
		ch = vnt_channels_2ghz;

		for (i = 0; i < ARRAY_SIZE(vnt_channels_2ghz); i++) {
			ch[i].max_power = VNT_RF_MAX_POWER;
			ch[i].flags = IEEE80211_CHAN_NO_HT40;
		}

		priv->hw->wiphy->bands[NL80211_BAND_2GHZ] =
						&vnt_supported_2ghz_band;
		break;
	}
}