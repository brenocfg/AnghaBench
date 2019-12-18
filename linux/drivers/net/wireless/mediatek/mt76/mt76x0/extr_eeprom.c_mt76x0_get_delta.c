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
typedef  int u8 ;
typedef  int u16 ;
struct cfg80211_chan_def {scalar_t__ width; TYPE_2__* chan; } ;
struct TYPE_3__ {struct cfg80211_chan_def chandef; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_4__ {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_5G_TARGET_POWER ; 
 int /*<<< orphan*/  MT_EE_TX_POWER_DELTA_BW40 ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ NL80211_CHAN_WIDTH_40 ; 
 scalar_t__ NL80211_CHAN_WIDTH_80 ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_rate_power_val (int) ; 

__attribute__((used)) static s8 mt76x0_get_delta(struct mt76x02_dev *dev)
{
	struct cfg80211_chan_def *chandef = &dev->mt76.chandef;
	u8 val;

	if (chandef->width == NL80211_CHAN_WIDTH_80) {
		val = mt76x02_eeprom_get(dev, MT_EE_5G_TARGET_POWER) >> 8;
	} else if (chandef->width == NL80211_CHAN_WIDTH_40) {
		u16 data;

		data = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_DELTA_BW40);
		if (chandef->chan->band == NL80211_BAND_5GHZ)
			val = data >> 8;
		else
			val = data;
	} else {
		return 0;
	}

	return mt76x02_rate_power_val(val);
}