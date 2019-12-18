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
struct mt7615_dev {int /*<<< orphan*/  mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7615_EEPROM_SIZE ; 
 int mt7615_efuse_init (struct mt7615_dev*) ; 
 int mt76_eeprom_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7615_eeprom_load(struct mt7615_dev *dev)
{
	int ret;

	ret = mt76_eeprom_init(&dev->mt76, MT7615_EEPROM_SIZE);
	if (ret < 0)
		return ret;

	return mt7615_efuse_init(dev);
}