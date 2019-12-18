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
struct mt7601u_dev {int dummy; } ;
typedef  enum mt7601u_eeprom_access_modes { ____Placeholder_mt7601u_eeprom_access_modes } mt7601u_eeprom_access_modes ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  MT_EFUSE_CTRL ; 
 int MT_EFUSE_CTRL_AIN ; 
 int MT_EFUSE_CTRL_AOUT ; 
 int MT_EFUSE_CTRL_KICK ; 
 int MT_EFUSE_CTRL_MODE ; 
 int /*<<< orphan*/  MT_EFUSE_DATA (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mt76_poll (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int mt76_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt7601u_efuse_read(struct mt7601u_dev *dev, u16 addr, u8 *data,
		   enum mt7601u_eeprom_access_modes mode)
{
	u32 val;
	int i;

	val = mt76_rr(dev, MT_EFUSE_CTRL);
	val &= ~(MT_EFUSE_CTRL_AIN |
		 MT_EFUSE_CTRL_MODE);
	val |= FIELD_PREP(MT_EFUSE_CTRL_AIN, addr & ~0xf) |
	       FIELD_PREP(MT_EFUSE_CTRL_MODE, mode) |
	       MT_EFUSE_CTRL_KICK;
	mt76_wr(dev, MT_EFUSE_CTRL, val);

	if (!mt76_poll(dev, MT_EFUSE_CTRL, MT_EFUSE_CTRL_KICK, 0, 1000))
		return -ETIMEDOUT;

	val = mt76_rr(dev, MT_EFUSE_CTRL);
	if ((val & MT_EFUSE_CTRL_AOUT) == MT_EFUSE_CTRL_AOUT) {
		/* Parts of eeprom not in the usage map (0x80-0xc0,0xf0)
		 * will not return valid data but it's ok.
		 */
		memset(data, 0xff, 16);
		return 0;
	}

	for (i = 0; i < 4; i++) {
		val = mt76_rr(dev, MT_EFUSE_DATA(i));
		put_unaligned_le32(val, data + 4 * i);
	}

	return 0;
}