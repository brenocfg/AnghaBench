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
typedef  int u16 ;
struct mt76x02_dev {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_NIC_CONF_0 ; 
 int MT_EE_NIC_CONF_0_PA_INT_2G ; 
 int MT_EE_NIC_CONF_0_PA_INT_5G ; 
 int NL80211_BAND_5GHZ ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

bool mt76x02_ext_pa_enabled(struct mt76x02_dev *dev, enum nl80211_band band)
{
	u16 conf0 = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_0);

	if (band == NL80211_BAND_5GHZ)
		return !(conf0 & MT_EE_NIC_CONF_0_PA_INT_5G);
	else
		return !(conf0 & MT_EE_NIC_CONF_0_PA_INT_2G);
}