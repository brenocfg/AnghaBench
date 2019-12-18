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
struct sd_info {int dummy; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 scalar_t__ CHK_MMC_DDR52 (struct sd_info*) ; 
 scalar_t__ CHK_SD (struct sd_info*) ; 
 scalar_t__ CHK_SD_DDR50 (struct sd_info*) ; 
 int MAX_PHASE ; 
 int /*<<< orphan*/  SD_CARD ; 
 int /*<<< orphan*/  SD_CFG3 ; 
 int /*<<< orphan*/  SD_NO_CARD ; 
 int /*<<< orphan*/  SD_RSP_80CLK_TIMEOUT_EN ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TUNE_TX ; 
 int detect_card_cd (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_change_phase (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int sd_ddr_tuning_tx_cmd (struct rtsx_chip*,int) ; 
 int sd_sdr_tuning_tx_cmd (struct rtsx_chip*,int) ; 
 int sd_search_final_phase (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_tuning_tx(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;
	int i, j;
	u32 raw_phase_map[3], phase_map;
	u8 final_phase;
	int (*tuning_cmd)(struct rtsx_chip *chip, u8 sample_point);

	if (CHK_SD(sd_card)) {
		if (CHK_SD_DDR50(sd_card))
			tuning_cmd = sd_ddr_tuning_tx_cmd;
		else
			tuning_cmd = sd_sdr_tuning_tx_cmd;

	} else {
		if (CHK_MMC_DDR52(sd_card))
			tuning_cmd = sd_ddr_tuning_tx_cmd;
		else
			return STATUS_FAIL;
	}

	for (i = 0; i < 3; i++) {
		raw_phase_map[i] = 0;
		for (j = MAX_PHASE; j >= 0; j--) {
			if (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) {
				sd_set_err_code(chip, SD_NO_CARD);
				rtsx_write_register(chip, SD_CFG3,
						    SD_RSP_80CLK_TIMEOUT_EN, 0);
				return STATUS_FAIL;
			}

			retval = tuning_cmd(chip, (u8)j);
			if (retval == STATUS_SUCCESS)
				raw_phase_map[i] |= 1 << j;
		}
	}

	phase_map = raw_phase_map[0] & raw_phase_map[1] & raw_phase_map[2];
	for (i = 0; i < 3; i++)
		dev_dbg(rtsx_dev(chip), "TX raw_phase_map[%d] = 0x%08x\n",
			i, raw_phase_map[i]);

	dev_dbg(rtsx_dev(chip), "TX phase_map = 0x%08x\n", phase_map);

	final_phase = sd_search_final_phase(chip, phase_map, TUNE_TX);
	if (final_phase == 0xFF)
		return STATUS_FAIL;

	retval = sd_change_phase(chip, final_phase, TUNE_TX);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}