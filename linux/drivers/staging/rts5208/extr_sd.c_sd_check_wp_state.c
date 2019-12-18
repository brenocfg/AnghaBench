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
typedef  int u16 ;
struct sd_info {int /*<<< orphan*/  sd_addr; } ;
struct rtsx_chip {int /*<<< orphan*/  card_wp; struct sd_info sd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_CMD ; 
 int /*<<< orphan*/  RTSX_BIPR ; 
 int /*<<< orphan*/  SD_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  SD_CARD ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int SD_STATUS ; 
 int /*<<< orphan*/  SD_TM_NORMAL_READ ; 
 int SD_WRITE_PROTECT ; 
 int /*<<< orphan*/  SEND_STATUS ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtsx_clear_sd_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_readl (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sd_read_data (struct rtsx_chip*,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ,int*,int,int) ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_check_wp_state(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;
	u32 val;
	u16 sd_card_type;
	u8 cmd[5], buf[64];

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
			      SD_BUS_WIDTH_4, buf, 64, 250);
	if (retval != STATUS_SUCCESS) {
		rtsx_clear_sd_error(chip);

		sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
				    SD_RSP_TYPE_R1, NULL, 0);
		return STATUS_FAIL;
	}

	dev_dbg(rtsx_dev(chip), "ACMD13:\n");
	dev_dbg(rtsx_dev(chip), "%*ph\n", 64, buf);

	sd_card_type = ((u16)buf[2] << 8) | buf[3];
	dev_dbg(rtsx_dev(chip), "sd_card_type = 0x%04x\n", sd_card_type);
	if ((sd_card_type == 0x0001) || (sd_card_type == 0x0002)) {
		/* ROM card or OTP */
		chip->card_wp |= SD_CARD;
	}

	/* Check SD Machanical Write-Protect Switch */
	val = rtsx_readl(chip, RTSX_BIPR);
	if (val & SD_WRITE_PROTECT)
		chip->card_wp |= SD_CARD;

	return STATUS_SUCCESS;
}