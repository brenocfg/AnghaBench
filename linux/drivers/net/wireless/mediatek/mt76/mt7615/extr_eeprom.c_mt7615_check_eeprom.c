#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct mt76_dev {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int EINVAL ; 
 int get_unaligned_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7615_check_eeprom(struct mt76_dev *dev)
{
	u16 val = get_unaligned_le16(dev->eeprom.data);

	switch (val) {
	case 0x7615:
		return 0;
	default:
		return -EINVAL;
	}
}