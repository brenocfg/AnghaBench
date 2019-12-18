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
typedef  int u16 ;
struct mt76x02_dev {int dummy; } ;
struct ieee80211_channel {scalar_t__ band; int hw_value; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_NIC_CONF_1 ; 
 int MT_EE_NIC_CONF_1_LNA_EXT_2G ; 
 int MT_EE_NIC_CONF_1_LNA_EXT_5G ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

u8 mt76x02_get_lna_gain(struct mt76x02_dev *dev,
			s8 *lna_2g, s8 *lna_5g,
			struct ieee80211_channel *chan)
{
	u16 val;
	u8 lna;

	val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1);
	if (val & MT_EE_NIC_CONF_1_LNA_EXT_2G)
		*lna_2g = 0;
	if (val & MT_EE_NIC_CONF_1_LNA_EXT_5G)
		memset(lna_5g, 0, sizeof(s8) * 3);

	if (chan->band == NL80211_BAND_2GHZ)
		lna = *lna_2g;
	else if (chan->hw_value <= 64)
		lna = lna_5g[0];
	else if (chan->hw_value <= 128)
		lna = lna_5g[1];
	else
		lna = lna_5g[2];

	return lna != 0xff ? lna : 0;
}