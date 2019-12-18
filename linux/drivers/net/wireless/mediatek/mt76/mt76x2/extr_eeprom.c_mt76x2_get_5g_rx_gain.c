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
struct mt76x02_dev {int dummy; } ;
typedef  enum mt76x2_cal_channel_group { ____Placeholder_mt76x2_cal_channel_group } mt76x2_cal_channel_group ;

/* Variables and functions */
#define  MT_CH_5G_JAPAN 132 
#define  MT_CH_5G_UNII_1 131 
#define  MT_CH_5G_UNII_2 130 
#define  MT_CH_5G_UNII_2E_1 129 
#define  MT_CH_5G_UNII_2E_2 128 
 int /*<<< orphan*/  MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN ; 
 int /*<<< orphan*/  MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN ; 
 int /*<<< orphan*/  MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int mt76x2_get_cal_channel_group (int) ; 

__attribute__((used)) static u8
mt76x2_get_5g_rx_gain(struct mt76x02_dev *dev, u8 channel)
{
	enum mt76x2_cal_channel_group group;

	group = mt76x2_get_cal_channel_group(channel);
	switch (group) {
	case MT_CH_5G_JAPAN:
		return mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN);
	case MT_CH_5G_UNII_1:
		return mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN) >> 8;
	case MT_CH_5G_UNII_2:
		return mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN);
	case MT_CH_5G_UNII_2E_1:
		return mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN) >> 8;
	case MT_CH_5G_UNII_2E_2:
		return mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN);
	default:
		return mt76x02_eeprom_get(dev,
					  MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN) >> 8;
	}
}