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
struct sd_info {int /*<<< orphan*/  sd_addr; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int ETIMEDOUT ; 
 scalar_t__ REG_SD_BLOCK_CNT_H ; 
 scalar_t__ REG_SD_BLOCK_CNT_L ; 
 scalar_t__ REG_SD_BYTE_CNT_H ; 
 scalar_t__ REG_SD_BYTE_CNT_L ; 
 scalar_t__ REG_SD_CFG1 ; 
 scalar_t__ REG_SD_CFG2 ; 
 scalar_t__ REG_SD_CMD0 ; 
 scalar_t__ REG_SD_TRANSFER ; 
 int SD_CALCULATE_CRC7 ; 
 int /*<<< orphan*/  SD_CARD ; 
 int SD_CHECK_CRC16 ; 
 int SD_CHECK_CRC7 ; 
 int SD_NO_WAIT_BUSY_END ; 
 int SD_RSP_LEN_6 ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int SD_TRANSFER_END ; 
 int SD_TRANSFER_START ; 
 int /*<<< orphan*/  SEND_STATUS ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int rtsx_write_ppbuf (struct rtsx_chip*,int*,int) ; 
 int /*<<< orphan*/  sd_clr_err_code (struct rtsx_chip*) ; 
 int /*<<< orphan*/  sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_write_data(struct rtsx_chip *chip, u8 trans_mode,
			 u8 *cmd, int cmd_len, u16 byte_cnt, u16 blk_cnt,
			 u8 bus_width, u8 *buf, int buf_len, int timeout)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;
	int i;

	sd_clr_err_code(chip);

	if (!buf)
		buf_len = 0;

	if (buf_len > 512) {
		/* This function can't write data more than one page */
		return STATUS_FAIL;
	}

	if (buf && buf_len) {
		retval = rtsx_write_ppbuf(chip, buf, buf_len);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;
	}

	rtsx_init_cmd(chip);

	if (cmd_len) {
		dev_dbg(rtsx_dev(chip), "SD/MMC CMD %d\n", cmd[0] - 0x40);
		for (i = 0; i < (min(cmd_len, 6)); i++) {
			rtsx_add_cmd(chip, WRITE_REG_CMD,
				     REG_SD_CMD0 + i, 0xFF, cmd[i]);
		}
	}
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF,
		     (u8)byte_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF,
		     (u8)(byte_cnt >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF,
		     (u8)blk_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF,
		     (u8)(blk_cnt >> 8));

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG1, 0x03, bus_width);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF,
		     SD_CALCULATE_CRC7 | SD_CHECK_CRC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CRC7 | SD_RSP_LEN_6);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
		     trans_mode | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER, SD_TRANSFER_END,
		     SD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, SD_CARD, timeout);
	if (retval < 0) {
		if (retval == -ETIMEDOUT) {
			sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
					    SD_RSP_TYPE_R1, NULL, 0);
		}

		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}