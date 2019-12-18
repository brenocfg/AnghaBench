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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_3__ {int physical_size; } ;
struct rtw_dev {TYPE_1__ efuse; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cfg_ldo25 ) (struct rtw_dev*,int) ;} ;

/* Variables and functions */
 int BITS_EF_ADDR ; 
 int BIT_EF_FLAG ; 
 int BIT_MASK_EF_ADDR ; 
 int BIT_MASK_EF_DATA ; 
 int BIT_SHIFT_EF_ADDR ; 
 int EBUSY ; 
 int /*<<< orphan*/  REG_EFUSE_CTRL ; 
 int rtw_read32 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  switch_efuse_bank (struct rtw_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rtw_dump_physical_efuse_map(struct rtw_dev *rtwdev, u8 *map)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	u32 size = rtwdev->efuse.physical_size;
	u32 efuse_ctl;
	u32 addr;
	u32 cnt;

	switch_efuse_bank(rtwdev);

	/* disable 2.5V LDO */
	chip->ops->cfg_ldo25(rtwdev, false);

	efuse_ctl = rtw_read32(rtwdev, REG_EFUSE_CTRL);

	for (addr = 0; addr < size; addr++) {
		efuse_ctl &= ~(BIT_MASK_EF_DATA | BITS_EF_ADDR);
		efuse_ctl |= (addr & BIT_MASK_EF_ADDR) << BIT_SHIFT_EF_ADDR;
		rtw_write32(rtwdev, REG_EFUSE_CTRL, efuse_ctl & (~BIT_EF_FLAG));

		cnt = 1000000;
		do {
			udelay(1);
			efuse_ctl = rtw_read32(rtwdev, REG_EFUSE_CTRL);
			if (--cnt == 0)
				return -EBUSY;
		} while (!(efuse_ctl & BIT_EF_FLAG));

		*(map + addr) = (u8)(efuse_ctl & BIT_MASK_EF_DATA);
	}

	return 0;
}