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
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; } ;
struct mt76x02_dev {TYPE_3__ mt76; } ;
struct TYPE_4__ {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_NIC_CONF_1 ; 
 int MT_EE_NIC_CONF_1_LNA_EXT_2G ; 
 int MT_EE_NIC_CONF_1_LNA_EXT_5G ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
mt76x2_has_ext_lna(struct mt76x02_dev *dev)
{
	u32 val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1);

	if (dev->mt76.chandef.chan->band == NL80211_BAND_2GHZ)
		return val & MT_EE_NIC_CONF_1_LNA_EXT_2G;
	else
		return val & MT_EE_NIC_CONF_1_LNA_EXT_5G;
}