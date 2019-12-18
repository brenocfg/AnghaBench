#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int has_5ghz; int has_2ghz; } ;
struct TYPE_4__ {TYPE_1__ cap; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;

/* Variables and functions */
#define  BOARD_TYPE_2GHZ 129 
#define  BOARD_TYPE_5GHZ 128 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_0 ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_0_BOARD_TYPE ; 
 int /*<<< orphan*/  mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

void mt76x02_eeprom_parse_hw_cap(struct mt76x02_dev *dev)
{
	u16 val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_0);

	switch (FIELD_GET(MT_EE_NIC_CONF_0_BOARD_TYPE, val)) {
	case BOARD_TYPE_5GHZ:
		dev->mt76.cap.has_5ghz = true;
		break;
	case BOARD_TYPE_2GHZ:
		dev->mt76.cap.has_2ghz = true;
		break;
	default:
		dev->mt76.cap.has_2ghz = true;
		dev->mt76.cap.has_5ghz = true;
		break;
	}
}