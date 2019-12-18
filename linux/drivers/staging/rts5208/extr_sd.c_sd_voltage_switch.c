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
struct rtsx_chip {int /*<<< orphan*/  sd_voltage_switch_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_CLK_EN ; 
 int /*<<< orphan*/  SD_BUS_STAT ; 
 int SD_CLK_FORCE_STOP ; 
 int SD_CLK_TOGGLE_EN ; 
 int SD_CMD_STATUS ; 
 int SD_DAT0_STATUS ; 
 int SD_DAT1_STATUS ; 
 int SD_DAT2_STATUS ; 
 int SD_DAT3_STATUS ; 
 int /*<<< orphan*/  SD_IO_1V8 ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  VOLTAGE_SWITCH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int sd_change_bank_voltage (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int sd_voltage_switch(struct rtsx_chip *chip)
{
	int retval;
	u8 stat;

	retval = rtsx_write_register(chip, SD_BUS_STAT,
				     SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP,
				     SD_CLK_TOGGLE_EN);
	if (retval)
		return retval;

	retval = sd_send_cmd_get_rsp(chip, VOLTAGE_SWITCH, 0, SD_RSP_TYPE_R1,
				     NULL, 0);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	udelay(chip->sd_voltage_switch_delay);

	retval = rtsx_read_register(chip, SD_BUS_STAT, &stat);
	if (retval)
		return retval;
	if (stat & (SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS)) {
		return STATUS_FAIL;
	}

	retval = rtsx_write_register(chip, SD_BUS_STAT, 0xFF,
				     SD_CLK_FORCE_STOP);
	if (retval)
		return retval;
	retval = sd_change_bank_voltage(chip, SD_IO_1V8);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	wait_timeout(50);

	retval = rtsx_write_register(chip, SD_BUS_STAT, 0xFF,
				     SD_CLK_TOGGLE_EN);
	if (retval)
		return retval;
	wait_timeout(10);

	retval = rtsx_read_register(chip, SD_BUS_STAT, &stat);
	if (retval)
		return retval;
	if ((stat & (SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS)) !=
			(SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS)) {
		dev_dbg(rtsx_dev(chip), "SD_BUS_STAT: 0x%x\n", stat);
		rtsx_write_register(chip, SD_BUS_STAT, SD_CLK_TOGGLE_EN |
				    SD_CLK_FORCE_STOP, 0);
		rtsx_write_register(chip, CARD_CLK_EN, 0xFF, 0);
		return STATUS_FAIL;
	}

	retval = rtsx_write_register(chip, SD_BUS_STAT,
				     SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP, 0);
	if (retval)
		return retval;

	return STATUS_SUCCESS;
}