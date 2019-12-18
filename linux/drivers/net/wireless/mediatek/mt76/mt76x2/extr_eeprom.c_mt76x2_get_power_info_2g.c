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
typedef  void* u8 ;
typedef  int u16 ;
struct mt76x2_tx_power_info {int target_power; TYPE_1__* chain; } ;
struct mt76x02_dev {int dummy; } ;
struct ieee80211_channel {int hw_value; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {int /*<<< orphan*/  delta; void* target_power; void* tssi_offset; void* tssi_slope; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_RF_2G_TSSI_OFF_TXPOWER ; 
 int /*<<< orphan*/  mt76x02_eeprom_copy (struct mt76x02_dev*,int,void**,int) ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_sign_extend_optional (void*,int) ; 

__attribute__((used)) static void
mt76x2_get_power_info_2g(struct mt76x02_dev *dev,
			 struct mt76x2_tx_power_info *t,
			 struct ieee80211_channel *chan,
			 int chain, int offset)
{
	int channel = chan->hw_value;
	int delta_idx;
	u8 data[6];
	u16 val;

	if (channel < 6)
		delta_idx = 3;
	else if (channel < 11)
		delta_idx = 4;
	else
		delta_idx = 5;

	mt76x02_eeprom_copy(dev, offset, data, sizeof(data));

	t->chain[chain].tssi_slope = data[0];
	t->chain[chain].tssi_offset = data[1];
	t->chain[chain].target_power = data[2];
	t->chain[chain].delta =
		mt76x02_sign_extend_optional(data[delta_idx], 7);

	val = mt76x02_eeprom_get(dev, MT_EE_RF_2G_TSSI_OFF_TXPOWER);
	t->target_power = val >> 8;
}