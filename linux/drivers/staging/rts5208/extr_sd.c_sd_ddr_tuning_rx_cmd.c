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
struct sd_info {int /*<<< orphan*/  sd_addr; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_CMD ; 
 int /*<<< orphan*/  SD_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int SD_STATUS ; 
 int /*<<< orphan*/  SD_TM_NORMAL_READ ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TUNE_RX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtsx_clear_sd_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int sd_change_phase (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int sd_read_data (struct rtsx_chip*,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_wait_data_idle (struct rtsx_chip*) ; 

__attribute__((used)) static int sd_ddr_tuning_rx_cmd(struct rtsx_chip *chip, u8 sample_point)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;
	u8 cmd[5];

	retval = sd_change_phase(chip, sample_point, TUNE_RX);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	dev_dbg(rtsx_dev(chip), "sd ddr tuning rx\n");

	retval = sd_send_cmd_get_rsp(chip, APP_CMD, sd_card->sd_addr,
				     SD_RSP_TYPE_R1, NULL, 0);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	cmd[0] = 0x40 | SD_STATUS;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	retval = sd_read_data(chip, SD_TM_NORMAL_READ, cmd, 5, 64, 1,
			      SD_BUS_WIDTH_4, NULL, 0, 100);
	if (retval != STATUS_SUCCESS) {
		(void)sd_wait_data_idle(chip);

		rtsx_clear_sd_error(chip);
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}