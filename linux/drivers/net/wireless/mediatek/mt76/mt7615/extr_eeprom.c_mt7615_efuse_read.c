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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct mt7615_dev {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int FIELD_PREP (int,int) ; 
 int MT_EFUSE_CTRL ; 
 int MT_EFUSE_CTRL_AIN ; 
 int MT_EFUSE_CTRL_AOUT ; 
 int MT_EFUSE_CTRL_KICK ; 
 int MT_EFUSE_CTRL_MODE ; 
 int MT_EFUSE_CTRL_VALID ; 
 int MT_EFUSE_RDATA (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mt76_poll (struct mt7615_dev*,int,int,int /*<<< orphan*/ ,int) ; 
 int mt76_rr (struct mt7615_dev*,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7615_dev*,int,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mt7615_efuse_read(struct mt7615_dev *dev, u32 base,
			     u16 addr, u8 *data)
{
	u32 val;
	int i;

	val = mt76_rr(dev, base + MT_EFUSE_CTRL);
	val &= ~(MT_EFUSE_CTRL_AIN | MT_EFUSE_CTRL_MODE);
	val |= FIELD_PREP(MT_EFUSE_CTRL_AIN, addr & ~0xf);
	val |= MT_EFUSE_CTRL_KICK;
	mt76_wr(dev, base + MT_EFUSE_CTRL, val);

	if (!mt76_poll(dev, base + MT_EFUSE_CTRL, MT_EFUSE_CTRL_KICK, 0, 1000))
		return -ETIMEDOUT;

	udelay(2);

	val = mt76_rr(dev, base + MT_EFUSE_CTRL);
	if ((val & MT_EFUSE_CTRL_AOUT) == MT_EFUSE_CTRL_AOUT ||
	    WARN_ON_ONCE(!(val & MT_EFUSE_CTRL_VALID))) {
		memset(data, 0x0, 16);
		return 0;
	}

	for (i = 0; i < 4; i++) {
		val = mt76_rr(dev, base + MT_EFUSE_RDATA(i));
		put_unaligned_le32(val, data + 4 * i);
	}

	return 0;
}