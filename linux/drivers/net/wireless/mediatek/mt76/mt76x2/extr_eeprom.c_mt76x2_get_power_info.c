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
typedef  int u16 ;
struct mt76x2_tx_power_info {void* delta_bw80; void* delta_bw40; TYPE_1__* chain; int /*<<< orphan*/  target_power; } ;
struct mt76x02_dev {int dummy; } ;
struct ieee80211_channel {scalar_t__ band; } ;
struct TYPE_2__ {int /*<<< orphan*/  target_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_TX_POWER_0_START_2G ; 
 int /*<<< orphan*/  MT_EE_TX_POWER_0_START_5G ; 
 int /*<<< orphan*/  MT_EE_TX_POWER_1_START_2G ; 
 int /*<<< orphan*/  MT_EE_TX_POWER_1_START_5G ; 
 int /*<<< orphan*/  MT_EE_TX_POWER_DELTA_BW40 ; 
 int /*<<< orphan*/  MT_EE_TX_POWER_DELTA_BW80 ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  memset (struct mt76x2_tx_power_info*,int /*<<< orphan*/ ,int) ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_field_valid (int /*<<< orphan*/ ) ; 
 void* mt76x02_rate_power_val (int) ; 
 int /*<<< orphan*/  mt76x2_get_power_info_2g (struct mt76x02_dev*,struct mt76x2_tx_power_info*,struct ieee80211_channel*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_get_power_info_5g (struct mt76x02_dev*,struct mt76x2_tx_power_info*,struct ieee80211_channel*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mt76x2_tssi_enabled (struct mt76x02_dev*) ; 

void mt76x2_get_power_info(struct mt76x02_dev *dev,
			   struct mt76x2_tx_power_info *t,
			   struct ieee80211_channel *chan)
{
	u16 bw40, bw80;

	memset(t, 0, sizeof(*t));

	bw40 = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_DELTA_BW40);
	bw80 = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_DELTA_BW80);

	if (chan->band == NL80211_BAND_5GHZ) {
		bw40 >>= 8;
		mt76x2_get_power_info_5g(dev, t, chan, 0,
					 MT_EE_TX_POWER_0_START_5G);
		mt76x2_get_power_info_5g(dev, t, chan, 1,
					 MT_EE_TX_POWER_1_START_5G);
	} else {
		mt76x2_get_power_info_2g(dev, t, chan, 0,
					 MT_EE_TX_POWER_0_START_2G);
		mt76x2_get_power_info_2g(dev, t, chan, 1,
					 MT_EE_TX_POWER_1_START_2G);
	}

	if (mt76x2_tssi_enabled(dev) ||
	    !mt76x02_field_valid(t->target_power))
		t->target_power = t->chain[0].target_power;

	t->delta_bw40 = mt76x02_rate_power_val(bw40);
	t->delta_bw80 = mt76x02_rate_power_val(bw80);
}