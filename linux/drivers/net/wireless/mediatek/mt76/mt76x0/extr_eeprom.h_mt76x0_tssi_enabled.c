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
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_NIC_CONF_1 ; 
 int MT_EE_NIC_CONF_1_TX_ALC_EN ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool mt76x0_tssi_enabled(struct mt76x02_dev *dev)
{
	return (mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1) &
		MT_EE_NIC_CONF_1_TX_ALC_EN);
}