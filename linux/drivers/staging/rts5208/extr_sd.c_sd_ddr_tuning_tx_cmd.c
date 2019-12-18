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
struct sd_info {int /*<<< orphan*/  sd_addr; int /*<<< orphan*/  raw_csd; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 scalar_t__ CHK_MMC_4BIT (struct sd_info*) ; 
 scalar_t__ CHK_MMC_8BIT (struct sd_info*) ; 
 scalar_t__ CHK_SD (struct sd_info*) ; 
 int PROGRAM_CSD ; 
 int SD_BUS_WIDTH_1 ; 
 int SD_BUS_WIDTH_4 ; 
 int SD_BUS_WIDTH_8 ; 
 int /*<<< orphan*/  SD_CFG3 ; 
 int /*<<< orphan*/  SD_RSP_80CLK_TIMEOUT_EN ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int /*<<< orphan*/  SD_TM_AUTO_WRITE_2 ; 
 int /*<<< orphan*/  SEND_STATUS ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TUNE_TX ; 
 int /*<<< orphan*/  rtsx_clear_sd_error (struct rtsx_chip*) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_change_phase (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_wait_state_data_ready (struct rtsx_chip*,int,int,int) ; 
 int sd_write_data (struct rtsx_chip*,int /*<<< orphan*/ ,int*,int,int,int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sd_ddr_tuning_tx_cmd(struct rtsx_chip *chip, u8 sample_point)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;
	u8 cmd[5], bus_width;

	retval = sd_change_phase(chip, sample_point, TUNE_TX);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	if (CHK_SD(sd_card)) {
		bus_width = SD_BUS_WIDTH_4;
	} else {
		if (CHK_MMC_8BIT(sd_card))
			bus_width = SD_BUS_WIDTH_8;
		else if (CHK_MMC_4BIT(sd_card))
			bus_width = SD_BUS_WIDTH_4;
		else
			bus_width = SD_BUS_WIDTH_1;
	}

	retval = sd_wait_state_data_ready(chip, 0x08, 1, 1000);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = rtsx_write_register(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     SD_RSP_80CLK_TIMEOUT_EN);
	if (retval)
		return retval;

	cmd[0] = 0x40 | PROGRAM_CSD;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	retval = sd_write_data(chip, SD_TM_AUTO_WRITE_2, cmd, 5, 16, 1,
			       bus_width, sd_card->raw_csd, 16, 100);
	if (retval != STATUS_SUCCESS) {
		rtsx_clear_sd_error(chip);
		rtsx_write_register(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN, 0);
		return STATUS_FAIL;
	}

	retval = rtsx_write_register(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     0);
	if (retval)
		return retval;

	sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr, SD_RSP_TYPE_R1,
			    NULL, 0);

	return STATUS_SUCCESS;
}