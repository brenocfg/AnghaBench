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

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_1 ; 
 int MT_EE_NIC_CONF_1_TEMP_TX_ALC ; 
 int /*<<< orphan*/  MT_EE_TX_POWER_EXT_PA_5G ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
mt76x2_temp_tx_alc_enabled(struct mt76x02_dev *dev)
{
	u16 val;

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_EXT_PA_5G);
	if (!(val & BIT(15)))
		return false;

	return mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1) &
	       MT_EE_NIC_CONF_1_TEMP_TX_ALC;
}