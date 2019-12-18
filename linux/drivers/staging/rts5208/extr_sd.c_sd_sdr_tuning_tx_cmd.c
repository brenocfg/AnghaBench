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
struct sd_info {int /*<<< orphan*/  sd_addr; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CFG3 ; 
 int /*<<< orphan*/  SD_RSP_80CLK_TIMEOUT_EN ; 
 int /*<<< orphan*/  SD_RSP_TIMEOUT ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int /*<<< orphan*/  SEND_STATUS ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TUNE_TX ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_change_phase (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_check_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_sdr_tuning_tx_cmd(struct rtsx_chip *chip, u8 sample_point)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;

	retval = sd_change_phase(chip, sample_point, TUNE_TX);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = rtsx_write_register(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     SD_RSP_80CLK_TIMEOUT_EN);
	if (retval)
		return retval;

	retval = sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
				     SD_RSP_TYPE_R1, NULL, 0);
	if (retval != STATUS_SUCCESS) {
		if (sd_check_err_code(chip, SD_RSP_TIMEOUT)) {
			rtsx_write_register(chip, SD_CFG3,
					    SD_RSP_80CLK_TIMEOUT_EN, 0);
			return STATUS_FAIL;
		}
	}

	retval = rtsx_write_register(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     0);
	if (retval)
		return retval;

	return STATUS_SUCCESS;
}