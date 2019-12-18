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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ data; scalar_t__ size; } ;
struct TYPE_4__ {TYPE_1__ eeprom; int /*<<< orphan*/  dev; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MT7612U_EEPROM_SIZE ; 
 int /*<<< orphan*/  MT_VEND_ADDR (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ devm_kzalloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_eeprom_parse_hw_cap (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  put_unaligned_le32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mt76x2u_init_eeprom(struct mt76x02_dev *dev)
{
	u32 val, i;

	dev->mt76.eeprom.data = devm_kzalloc(dev->mt76.dev,
					     MT7612U_EEPROM_SIZE,
					     GFP_KERNEL);
	dev->mt76.eeprom.size = MT7612U_EEPROM_SIZE;
	if (!dev->mt76.eeprom.data)
		return -ENOMEM;

	for (i = 0; i + 4 <= MT7612U_EEPROM_SIZE; i += 4) {
		val = mt76_rr(dev, MT_VEND_ADDR(EEPROM, i));
		put_unaligned_le32(val, dev->mt76.eeprom.data + i);
	}

	mt76x02_eeprom_parse_hw_cap(dev);
	return 0;
}