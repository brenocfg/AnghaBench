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
struct sd_info {int /*<<< orphan*/  sd_addr; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 int MAX_PHASE ; 
 int /*<<< orphan*/  SD_CARD ; 
 int /*<<< orphan*/  SD_CFG3 ; 
 int /*<<< orphan*/  SD_NO_CARD ; 
 int /*<<< orphan*/  SD_RSP_80CLK_TIMEOUT_EN ; 
 int /*<<< orphan*/  SD_RSP_TIMEOUT ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int /*<<< orphan*/  SEND_STATUS ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TUNE_TX ; 
 int detect_card_cd (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_change_phase (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_check_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sd_search_final_phase (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_ddr_pre_tuning_tx(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;
	int i;
	u32 phase_map;
	u8 final_phase;

	retval = rtsx_write_register(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     SD_RSP_80CLK_TIMEOUT_EN);
	if (retval)
		return retval;

	phase_map = 0;
	for (i = MAX_PHASE; i >= 0; i--) {
		if (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) {
			sd_set_err_code(chip, SD_NO_CARD);
			rtsx_write_register(chip, SD_CFG3,
					    SD_RSP_80CLK_TIMEOUT_EN, 0);
			return STATUS_FAIL;
		}

		retval = sd_change_phase(chip, (u8)i, TUNE_TX);
		if (retval != STATUS_SUCCESS)
			continue;

		retval = sd_send_cmd_get_rsp(chip, SEND_STATUS,
					     sd_card->sd_addr, SD_RSP_TYPE_R1,
					     NULL, 0);
		if ((retval == STATUS_SUCCESS) ||
		    !sd_check_err_code(chip, SD_RSP_TIMEOUT))
			phase_map |= 1 << i;
	}

	retval = rtsx_write_register(chip, SD_CFG3, SD_RSP_80CLK_TIMEOUT_EN,
				     0);
	if (retval)
		return retval;

	dev_dbg(rtsx_dev(chip), "DDR TX pre tune phase_map = 0x%08x\n",
		phase_map);

	final_phase = sd_search_final_phase(chip, phase_map, TUNE_TX);
	if (final_phase == 0xFF)
		return STATUS_FAIL;

	retval = sd_change_phase(chip, final_phase, TUNE_TX);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	dev_dbg(rtsx_dev(chip), "DDR TX pre tune phase: %d\n",
		(int)final_phase);

	return STATUS_SUCCESS;
}