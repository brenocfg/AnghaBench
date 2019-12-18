#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_7__ {int has_2ghz; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_9__ {TYPE_3__ eeprom; scalar_t__ macaddr; TYPE_2__ cap; TYPE_1__ otp; } ;
struct mt7603_dev {TYPE_4__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MT7603_EEPROM_SIZE ; 
 scalar_t__ MT_EE_MAC_ADDR ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7603_apply_cal_free_data (struct mt7603_dev*,scalar_t__) ; 
 scalar_t__ mt7603_check_eeprom (TYPE_4__*) ; 
 int mt7603_eeprom_load (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_eeprom_override (TYPE_4__*) ; 

int mt7603_eeprom_init(struct mt7603_dev *dev)
{
	int ret;

	ret = mt7603_eeprom_load(dev);
	if (ret < 0)
		return ret;

	if (dev->mt76.otp.data) {
		if (mt7603_check_eeprom(&dev->mt76) == 0)
			mt7603_apply_cal_free_data(dev, dev->mt76.otp.data);
		else
			memcpy(dev->mt76.eeprom.data, dev->mt76.otp.data,
			       MT7603_EEPROM_SIZE);
	}

	dev->mt76.cap.has_2ghz = true;
	memcpy(dev->mt76.macaddr, dev->mt76.eeprom.data + MT_EE_MAC_ADDR,
	       ETH_ALEN);

	mt76_eeprom_override(&dev->mt76);

	return 0;
}