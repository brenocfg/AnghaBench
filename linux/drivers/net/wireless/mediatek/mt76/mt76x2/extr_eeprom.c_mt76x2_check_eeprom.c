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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ eeprom; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MT_EE_PCI_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int get_unaligned_le16 (scalar_t__) ; 

__attribute__((used)) static int mt76x2_check_eeprom(struct mt76x02_dev *dev)
{
	u16 val = get_unaligned_le16(dev->mt76.eeprom.data);

	if (!val)
		val = get_unaligned_le16(dev->mt76.eeprom.data + MT_EE_PCI_ID);

	switch (val) {
	case 0x7662:
	case 0x7612:
		return 0;
	default:
		dev_err(dev->mt76.dev, "EEPROM data check failed: %04x\n", val);
		return -EINVAL;
	}
}