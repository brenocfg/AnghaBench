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
typedef  int u8 ;
typedef  int u32 ;
struct rtsx_chip {int asic_code; int aux_pwr_exist; int hw_bypass_sd; int auto_delink_en; int /*<<< orphan*/  lun_mode; scalar_t__ use_hw_setting; int /*<<< orphan*/  baro_pkg; scalar_t__ phy_debug_mode; scalar_t__ ic_version; } ;

/* Variables and functions */
 int AUX_PWR_DETECTED ; 
 int CARD_SHARE_MODE ; 
 int CHANGE_LINK_STATE ; 
 scalar_t__ CHECK_BARO_PKG (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int CLK_SEL ; 
 int /*<<< orphan*/  CLR_SDIO_EXIST (struct rtsx_chip*) ; 
 int /*<<< orphan*/  DEFAULT_SINGLE ; 
 int /*<<< orphan*/  LQFP ; 
 int PDINFO ; 
 int /*<<< orphan*/  QFN ; 
 int /*<<< orphan*/  SD_MS_1LUN ; 
 int /*<<< orphan*/  SET_SDIO_EXIST (struct rtsx_chip*) ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_read_cfg_dw (struct rtsx_chip*,int /*<<< orphan*/ ,int,int*) ; 
 int rtsx_read_register (struct rtsx_chip*,int,int*) ; 
 int rtsx_write_register (struct rtsx_chip*,int,int,int) ; 

__attribute__((used)) static int rts5288_init(struct rtsx_chip *chip)
{
	int retval;
	u8 val = 0, max_func;
	u32 lval = 0;

	retval = rtsx_write_register(chip, CLK_SEL, 0x03, 0x03);
	if (retval)
		return retval;
	retval = rtsx_read_register(chip, CLK_SEL, &val);
	if (retval)
		return retval;
	chip->asic_code = val == 0 ? 1 : 0;

	chip->ic_version = 0;
	chip->phy_debug_mode = 0;

	retval = rtsx_read_register(chip, PDINFO, &val);
	if (retval)
		return retval;
	dev_dbg(rtsx_dev(chip), "PDINFO: 0x%x\n", val);
	chip->aux_pwr_exist = val & AUX_PWR_DETECTED ? 1 : 0;

	retval = rtsx_read_register(chip, CARD_SHARE_MODE, &val);
	if (retval)
		return retval;
	dev_dbg(rtsx_dev(chip), "CARD_SHARE_MODE: 0x%x\n", val);
	chip->baro_pkg = val & 0x04 ? QFN : LQFP;

	retval = rtsx_read_register(chip, 0xFE5A, &val);
	if (retval)
		return retval;
	chip->hw_bypass_sd = val & 0x10 ? 1 : 0;

	retval = rtsx_read_cfg_dw(chip, 0, 0x718, &lval);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	max_func = (u8)((lval >> 29) & 0x07);
	dev_dbg(rtsx_dev(chip), "Max function number: %d\n", max_func);
	if (max_func == 0x02)
		SET_SDIO_EXIST(chip);
	else
		CLR_SDIO_EXIST(chip);

	if (chip->use_hw_setting) {
		retval = rtsx_read_register(chip, CHANGE_LINK_STATE, &val);
		if (retval)
			return retval;
		chip->auto_delink_en = val & 0x80 ? 1 : 0;

		if (CHECK_BARO_PKG(chip, LQFP))
			chip->lun_mode = SD_MS_1LUN;
		else
			chip->lun_mode = DEFAULT_SINGLE;
	}

	return STATUS_SUCCESS;
}