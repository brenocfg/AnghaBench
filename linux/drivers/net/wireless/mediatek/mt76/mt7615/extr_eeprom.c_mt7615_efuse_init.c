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
typedef  int u32 ;
struct TYPE_3__ {int size; void* data; } ;
struct TYPE_4__ {TYPE_1__ otp; int /*<<< orphan*/  dev; } ;
struct mt7615_dev {TYPE_2__ mt76; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MT7615_EEPROM_SIZE ; 
 int /*<<< orphan*/  MT_EFUSE_BASE ; 
 int MT_EFUSE_BASE_CTRL ; 
 int MT_EFUSE_BASE_CTRL_EMPTY ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mt7615_efuse_read (struct mt7615_dev*,int,int,void*) ; 
 int mt7615_reg_map (struct mt7615_dev*,int /*<<< orphan*/ ) ; 
 int mt76_rr (struct mt7615_dev*,int) ; 

__attribute__((used)) static int mt7615_efuse_init(struct mt7615_dev *dev)
{
	u32 val, base = mt7615_reg_map(dev, MT_EFUSE_BASE);
	int i, len = MT7615_EEPROM_SIZE;
	void *buf;

	val = mt76_rr(dev, base + MT_EFUSE_BASE_CTRL);
	if (val & MT_EFUSE_BASE_CTRL_EMPTY)
		return 0;

	dev->mt76.otp.data = devm_kzalloc(dev->mt76.dev, len, GFP_KERNEL);
	dev->mt76.otp.size = len;
	if (!dev->mt76.otp.data)
		return -ENOMEM;

	buf = dev->mt76.otp.data;
	for (i = 0; i + 16 <= len; i += 16) {
		int ret;

		ret = mt7615_efuse_read(dev, base, i, buf + i);
		if (ret)
			return ret;
	}

	return 0;
}