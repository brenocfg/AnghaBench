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
typedef  int s8 ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_2 ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_2_XTAL_OPTION ; 
 int /*<<< orphan*/  MT_EE_XTAL_TRIM_1 ; 
 int /*<<< orphan*/  MT_EE_XTAL_TRIM_2 ; 
 int /*<<< orphan*/  MT_XO_CTRL5 ; 
 int /*<<< orphan*/  MT_XO_CTRL5_C2_VAL ; 
 int /*<<< orphan*/  MT_XO_CTRL6 ; 
 int /*<<< orphan*/  MT_XO_CTRL6_C2_CTRL ; 
 int /*<<< orphan*/  MT_XO_CTRL7 ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt76x2_fixup_xtal(struct mt76x02_dev *dev)
{
	u16 eep_val;
	s8 offset = 0;

	eep_val = mt76x02_eeprom_get(dev, MT_EE_XTAL_TRIM_2);

	offset = eep_val & 0x7f;
	if ((eep_val & 0xff) == 0xff)
		offset = 0;
	else if (eep_val & 0x80)
		offset = 0 - offset;

	eep_val >>= 8;
	if (eep_val == 0x00 || eep_val == 0xff) {
		eep_val = mt76x02_eeprom_get(dev, MT_EE_XTAL_TRIM_1);
		eep_val &= 0xff;

		if (eep_val == 0x00 || eep_val == 0xff)
			eep_val = 0x14;
	}

	eep_val &= 0x7f;
	mt76_rmw_field(dev, MT_XO_CTRL5, MT_XO_CTRL5_C2_VAL, eep_val + offset);
	mt76_set(dev, MT_XO_CTRL6, MT_XO_CTRL6_C2_CTRL);

	eep_val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_2);
	switch (FIELD_GET(MT_EE_NIC_CONF_2_XTAL_OPTION, eep_val)) {
	case 0:
		mt76_wr(dev, MT_XO_CTRL7, 0x5c1fee80);
		break;
	case 1:
		mt76_wr(dev, MT_XO_CTRL7, 0x5c1feed0);
		break;
	default:
		break;
	}
}