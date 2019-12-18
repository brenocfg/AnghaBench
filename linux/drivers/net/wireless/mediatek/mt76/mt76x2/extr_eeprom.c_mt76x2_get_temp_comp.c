#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct mt76x2_temp_comp {int temp_25_ref; int high_slope; int low_slope; int upper_bound; scalar_t__ lower_bound; } ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; } ;
struct mt76x02_dev {TYPE_3__ mt76; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_4__ {int band; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MT_EE_RF_TEMP_COMP_SLOPE_2G ; 
 int /*<<< orphan*/  MT_EE_RF_TEMP_COMP_SLOPE_5G ; 
 int /*<<< orphan*/  MT_EE_TX_POWER_DELTA_BW80 ; 
 int /*<<< orphan*/  MT_EE_TX_POWER_EXT_PA_5G ; 
 int NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  memset (struct mt76x2_temp_comp*,int /*<<< orphan*/ ,int) ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_ext_pa_enabled (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_temp_tx_alc_enabled (struct mt76x02_dev*) ; 

int mt76x2_get_temp_comp(struct mt76x02_dev *dev, struct mt76x2_temp_comp *t)
{
	enum nl80211_band band = dev->mt76.chandef.chan->band;
	u16 val, slope;
	u8 bounds;

	memset(t, 0, sizeof(*t));

	if (!mt76x2_temp_tx_alc_enabled(dev))
		return -EINVAL;

	if (!mt76x02_ext_pa_enabled(dev, band))
		return -EINVAL;

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_EXT_PA_5G) >> 8;
	t->temp_25_ref = val & 0x7f;
	if (band == NL80211_BAND_5GHZ) {
		slope = mt76x02_eeprom_get(dev, MT_EE_RF_TEMP_COMP_SLOPE_5G);
		bounds = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_EXT_PA_5G);
	} else {
		slope = mt76x02_eeprom_get(dev, MT_EE_RF_TEMP_COMP_SLOPE_2G);
		bounds = mt76x02_eeprom_get(dev,
					    MT_EE_TX_POWER_DELTA_BW80) >> 8;
	}

	t->high_slope = slope & 0xff;
	t->low_slope = slope >> 8;
	t->lower_bound = 0 - (bounds & 0xf);
	t->upper_bound = (bounds >> 4) & 0xf;

	return 0;
}