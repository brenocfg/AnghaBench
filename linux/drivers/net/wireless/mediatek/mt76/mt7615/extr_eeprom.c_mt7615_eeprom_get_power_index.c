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
struct mt7615_dev {int dummy; } ;
struct ieee80211_channel {scalar_t__ band; int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int EINVAL ; 
 int MT_EE_EXT_PA_2G_TARGET_POWER ; 
 int MT_EE_EXT_PA_5G_TARGET_POWER ; 
 int MT_EE_TX0_2G_TARGET_POWER ; 
 int MT_EE_TX0_5G_G0_TARGET_POWER ; 
 int MT_EE_TX1_5G_G0_TARGET_POWER ; 
 int MT_EE_TX2_5G_G0_TARGET_POWER ; 
 int MT_EE_TX3_5G_G0_TARGET_POWER ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ mt7615_ext_pa_enabled (struct mt7615_dev*,scalar_t__) ; 
 int mt7615_get_channel_group (int /*<<< orphan*/ ) ; 

int mt7615_eeprom_get_power_index(struct mt7615_dev *dev,
				  struct ieee80211_channel *chan,
				  u8 chain_idx)
{
	int index;

	if (chain_idx > 3)
		return -EINVAL;

	/* TSSI disabled */
	if (mt7615_ext_pa_enabled(dev, chan->band)) {
		if (chan->band == NL80211_BAND_2GHZ)
			return MT_EE_EXT_PA_2G_TARGET_POWER;
		else
			return MT_EE_EXT_PA_5G_TARGET_POWER;
	}

	/* TSSI enabled */
	if (chan->band == NL80211_BAND_2GHZ) {
		index = MT_EE_TX0_2G_TARGET_POWER + chain_idx * 6;
	} else {
		int group = mt7615_get_channel_group(chan->hw_value);

		switch (chain_idx) {
		case 1:
			index = MT_EE_TX1_5G_G0_TARGET_POWER;
			break;
		case 2:
			index = MT_EE_TX2_5G_G0_TARGET_POWER;
			break;
		case 3:
			index = MT_EE_TX3_5G_G0_TARGET_POWER;
			break;
		case 0:
		default:
			index = MT_EE_TX0_5G_G0_TARGET_POWER;
			break;
		}
		index += 5 * group;
	}

	return index;
}