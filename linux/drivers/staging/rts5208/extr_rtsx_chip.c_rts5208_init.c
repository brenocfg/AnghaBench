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
typedef  int u16 ;
struct rtsx_chip {int asic_code; int ic_version; int phy_debug_mode; int aux_pwr_exist; int hw_bypass_sd; int auto_delink_en; scalar_t__ use_hw_setting; } ;

/* Variables and functions */
 int AUX_PWR_DETECTED ; 
 int CHANGE_LINK_STATE ; 
 int CLK_SEL ; 
 int /*<<< orphan*/  CLR_SDIO_EXIST (struct rtsx_chip*) ; 
 int PDINFO ; 
 int PHY_DEBUG_MODE ; 
 int /*<<< orphan*/  SET_SDIO_EXIST (struct rtsx_chip*) ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_read_config_byte (struct rtsx_chip*,int,int*) ; 
 int rtsx_read_phy_register (struct rtsx_chip*,int,int*) ; 
 int rtsx_read_register (struct rtsx_chip*,int,int*) ; 
 int rtsx_write_register (struct rtsx_chip*,int,int,int) ; 

__attribute__((used)) static int rts5208_init(struct rtsx_chip *chip)
{
	int retval;
	u16 reg = 0;
	u8 val = 0;

	retval = rtsx_write_register(chip, CLK_SEL, 0x03, 0x03);
	if (retval)
		return retval;
	retval = rtsx_read_register(chip, CLK_SEL, &val);
	if (retval)
		return retval;
	chip->asic_code = val == 0 ? 1 : 0;

	if (chip->asic_code) {
		retval = rtsx_read_phy_register(chip, 0x1C, &reg);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		dev_dbg(rtsx_dev(chip), "Value of phy register 0x1C is 0x%x\n",
			reg);
		chip->ic_version = (reg >> 4) & 0x07;
		chip->phy_debug_mode = reg & PHY_DEBUG_MODE ? 1 : 0;

	} else {
		retval = rtsx_read_register(chip, 0xFE80, &val);
		if (retval)
			return retval;
		chip->ic_version = val;
		chip->phy_debug_mode = 0;
	}

	retval = rtsx_read_register(chip, PDINFO, &val);
	if (retval)
		return retval;
	dev_dbg(rtsx_dev(chip), "PDINFO: 0x%x\n", val);
	chip->aux_pwr_exist = val & AUX_PWR_DETECTED ? 1 : 0;

	retval = rtsx_read_register(chip, 0xFE50, &val);
	if (retval)
		return retval;
	chip->hw_bypass_sd = val & 0x01 ? 1 : 0;

	rtsx_read_config_byte(chip, 0x0E, &val);
	if (val & 0x80)
		SET_SDIO_EXIST(chip);
	else
		CLR_SDIO_EXIST(chip);

	if (chip->use_hw_setting) {
		retval = rtsx_read_register(chip, CHANGE_LINK_STATE, &val);
		if (retval)
			return retval;
		chip->auto_delink_en = val & 0x80 ? 1 : 0;
	}

	return STATUS_SUCCESS;
}