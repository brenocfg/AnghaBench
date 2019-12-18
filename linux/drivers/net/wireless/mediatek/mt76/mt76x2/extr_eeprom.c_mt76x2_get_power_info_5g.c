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
typedef  enum mt76x2_cal_channel_group { ____Placeholder_mt76x2_cal_channel_group } mt76x2_cal_channel_group ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {int /*<<< orphan*/  delta; void* target_power; void* tssi_offset; void* tssi_slope; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_RF_2G_RX_HIGH_GAIN ; 
 int MT_TX_POWER_GROUP_SIZE_5G ; 
 int /*<<< orphan*/  mt76x02_eeprom_copy (struct mt76x02_dev*,int,void**,int) ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_sign_extend_optional (void*,int) ; 
 int mt76x2_get_cal_channel_group (int) ; 

__attribute__((used)) static void
mt76x2_get_power_info_5g(struct mt76x02_dev *dev,
			 struct mt76x2_tx_power_info *t,
			 struct ieee80211_channel *chan,
			 int chain, int offset)
{
	int channel = chan->hw_value;
	enum mt76x2_cal_channel_group group;
	int delta_idx;
	u16 val;
	u8 data[5];

	group = mt76x2_get_cal_channel_group(channel);
	offset += group * MT_TX_POWER_GROUP_SIZE_5G;

	if (channel >= 192)
		delta_idx = 4;
	else if (channel >= 184)
		delta_idx = 3;
	else if (channel < 44)
		delta_idx = 3;
	else if (channel < 52)
		delta_idx = 4;
	else if (channel < 58)
		delta_idx = 3;
	else if (channel < 98)
		delta_idx = 4;
	else if (channel < 106)
		delta_idx = 3;
	else if (channel < 116)
		delta_idx = 4;
	else if (channel < 130)
		delta_idx = 3;
	else if (channel < 149)
		delta_idx = 4;
	else if (channel < 157)
		delta_idx = 3;
	else
		delta_idx = 4;

	mt76x02_eeprom_copy(dev, offset, data, sizeof(data));

	t->chain[chain].tssi_slope = data[0];
	t->chain[chain].tssi_offset = data[1];
	t->chain[chain].target_power = data[2];
	t->chain[chain].delta =
		mt76x02_sign_extend_optional(data[delta_idx], 7);

	val = mt76x02_eeprom_get(dev, MT_EE_RF_2G_RX_HIGH_GAIN);
	t->target_power = val & 0xff;
}