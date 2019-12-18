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
struct TYPE_6__ {int has_5ghz; int has_2ghz; } ;
struct TYPE_4__ {int* data; } ;
struct TYPE_5__ {TYPE_3__ cap; TYPE_1__ eeprom; } ;
struct mt7615_dev {TYPE_2__ mt76; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
#define  MT_EE_2GHZ 129 
#define  MT_EE_5GHZ 128 
 int /*<<< orphan*/  MT_EE_NIC_WIFI_CONF_BAND_SEL ; 
 size_t MT_EE_WIFI_CONF ; 

__attribute__((used)) static void mt7615_eeprom_parse_hw_cap(struct mt7615_dev *dev)
{
	u8 val, *eeprom = dev->mt76.eeprom.data;

	val = FIELD_GET(MT_EE_NIC_WIFI_CONF_BAND_SEL,
			eeprom[MT_EE_WIFI_CONF]);
	switch (val) {
	case MT_EE_5GHZ:
		dev->mt76.cap.has_5ghz = true;
		break;
	case MT_EE_2GHZ:
		dev->mt76.cap.has_2ghz = true;
		break;
	default:
		dev->mt76.cap.has_2ghz = true;
		dev->mt76.cap.has_5ghz = true;
		break;
	}
}