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
struct sd_info {int /*<<< orphan*/  sd_type; scalar_t__ capacity; } ;
struct rtsx_chip {size_t* card2lun; int sd_io; int sd_ctl; scalar_t__* capacity; scalar_t__ asic_code; scalar_t__ ignore_sd; struct sd_info sd_card; } ;

/* Variables and functions */
 scalar_t__ CHK_SDIO_EXIST (struct rtsx_chip*) ; 
 int /*<<< orphan*/  CHK_SDIO_IGNORED (struct rtsx_chip*) ; 
 int /*<<< orphan*/  FPGA_PULL_CTL ; 
 int FPGA_SD_PULL_CTL_BIT ; 
 int /*<<< orphan*/  REG_SD_BYTE_CNT_H ; 
 int /*<<< orphan*/  REG_SD_BYTE_CNT_L ; 
 int RESET_MMC_FIRST ; 
 size_t SD_CARD ; 
 int /*<<< orphan*/  SD_CLK_DIVIDE_0 ; 
 int /*<<< orphan*/  SD_NO_CARD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int card_share_mode (struct rtsx_chip*,size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int enable_card_clock (struct rtsx_chip*,size_t) ; 
 int /*<<< orphan*/  memset (struct sd_info*,int /*<<< orphan*/ ,int) ; 
 int reset_mmc (struct rtsx_chip*) ; 
 int reset_sd (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ sd_check_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sd_init_power (struct rtsx_chip*) ; 
 int /*<<< orphan*/  sd_init_reg_addr (struct rtsx_chip*) ; 
 int sd_pull_ctl_enable (struct rtsx_chip*) ; 
 int sd_set_clock_divider (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sd_set_init_para (struct rtsx_chip*) ; 

int reset_sd_card(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;

	sd_init_reg_addr(chip);

	memset(sd_card, 0, sizeof(struct sd_info));
	chip->capacity[chip->card2lun[SD_CARD]] = 0;

	retval = enable_card_clock(chip, SD_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	if (chip->ignore_sd && CHK_SDIO_EXIST(chip) &&
	    !CHK_SDIO_IGNORED(chip)) {
		if (chip->asic_code) {
			retval = sd_pull_ctl_enable(chip);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;
		} else {
			retval = rtsx_write_register(chip, FPGA_PULL_CTL,
						     FPGA_SD_PULL_CTL_BIT |
						     0x20, 0);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;
		}
		retval = card_share_mode(chip, SD_CARD);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		chip->sd_io = 1;
		return STATUS_FAIL;
	}

	retval = sd_init_power(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	if (chip->sd_ctl & RESET_MMC_FIRST) {
		retval = reset_mmc(chip);
		if (retval != STATUS_SUCCESS) {
			if (sd_check_err_code(chip, SD_NO_CARD))
				return STATUS_FAIL;

			retval = reset_sd(chip);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;
		}
	} else {
		retval = reset_sd(chip);
		if (retval != STATUS_SUCCESS) {
			if (sd_check_err_code(chip, SD_NO_CARD))
				return STATUS_FAIL;

			if (chip->sd_io)
				return STATUS_FAIL;
			retval = reset_mmc(chip);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;
		}
	}

	retval = sd_set_clock_divider(chip, SD_CLK_DIVIDE_0);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = rtsx_write_register(chip, REG_SD_BYTE_CNT_L, 0xFF, 0);
	if (retval)
		return retval;
	retval = rtsx_write_register(chip, REG_SD_BYTE_CNT_H, 0xFF, 2);
	if (retval)
		return retval;

	chip->capacity[chip->card2lun[SD_CARD]] = sd_card->capacity;

	retval = sd_set_init_para(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	dev_dbg(rtsx_dev(chip), "sd_card->sd_type = 0x%x\n", sd_card->sd_type);

	return STATUS_SUCCESS;
}