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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sd_info {int dummy; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 int BUSTEST_R ; 
 int /*<<< orphan*/  BUSTEST_W ; 
 scalar_t__ CARD_DATA_SOURCE ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 scalar_t__ CHK_MMC_DDR52 (struct sd_info*) ; 
 scalar_t__ MMC_8BIT_BUS ; 
 scalar_t__ MMC_SWITCH_ERR ; 
 int PINGPONG_BUFFER ; 
 scalar_t__ PPBUF_BASE2 ; 
 int /*<<< orphan*/  READ_REG_CMD ; 
 scalar_t__ REG_SD_BLOCK_CNT_H ; 
 scalar_t__ REG_SD_BLOCK_CNT_L ; 
 scalar_t__ REG_SD_BYTE_CNT_L ; 
 scalar_t__ REG_SD_CFG2 ; 
 int /*<<< orphan*/  REG_SD_CFG3 ; 
 scalar_t__ REG_SD_CMD0 ; 
 scalar_t__ REG_SD_TRANSFER ; 
 scalar_t__ SD_BUS_WIDTH_4 ; 
 scalar_t__ SD_BUS_WIDTH_8 ; 
 int SD_CALCULATE_CRC7 ; 
 int /*<<< orphan*/  SD_CARD ; 
 int SD_CHECK_CRC7 ; 
 int SD_NO_CHECK_CRC16 ; 
 int SD_NO_WAIT_BUSY_END ; 
 int SD_RSP_LEN_6 ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1b ; 
 int /*<<< orphan*/  SD_TM_AUTO_WRITE_3 ; 
 int SD_TM_NORMAL_READ ; 
 int SD_TRANSFER_END ; 
 int SD_TRANSFER_START ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  SWITCH ; 
 int SWITCH_ERR ; 
 int SWITCH_FAIL ; 
 int SWITCH_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_sd_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 scalar_t__* rtsx_get_cmd_data (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int sd_write_data (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__*,int,int) ; 

__attribute__((used)) static int mmc_test_switch_bus(struct rtsx_chip *chip, u8 width)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;
	u8 buf[8] = {0}, bus_width, *ptr;
	u16 byte_cnt;
	int len;

	retval = sd_send_cmd_get_rsp(chip, BUSTEST_W, 0, SD_RSP_TYPE_R1, NULL,
				     0);
	if (retval != STATUS_SUCCESS)
		return SWITCH_FAIL;

	if (width == MMC_8BIT_BUS) {
		buf[0] = 0x55;
		buf[1] = 0xAA;
		len = 8;
		byte_cnt = 8;
		bus_width = SD_BUS_WIDTH_8;
	} else {
		buf[0] = 0x5A;
		len = 4;
		byte_cnt = 4;
		bus_width = SD_BUS_WIDTH_4;
	}

	retval = rtsx_write_register(chip, REG_SD_CFG3, 0x02, 0x02);
	if (retval != STATUS_SUCCESS)
		return SWITCH_ERR;

	retval = sd_write_data(chip, SD_TM_AUTO_WRITE_3, NULL, 0, byte_cnt, 1,
			       bus_width, buf, len, 100);
	if (retval != STATUS_SUCCESS) {
		rtsx_clear_sd_error(chip);
		rtsx_write_register(chip, REG_SD_CFG3, 0x02, 0);
		return SWITCH_ERR;
	}

	retval = rtsx_write_register(chip, REG_SD_CFG3, 0x02, 0);
	if (retval != STATUS_SUCCESS)
		return SWITCH_ERR;

	dev_dbg(rtsx_dev(chip), "SD/MMC CMD %d\n", BUSTEST_R);

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0, 0xFF, 0x40 | BUSTEST_R);

	if (width == MMC_8BIT_BUS)
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L,
			     0xFF, 0x08);
	else
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L,
			     0xFF, 0x04);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF, 1);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF, 0);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF, SD_CALCULATE_CRC7 |
		     SD_NO_CHECK_CRC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CRC7 | SD_RSP_LEN_6);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01,
		     PINGPONG_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
		     SD_TM_NORMAL_READ | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER, SD_TRANSFER_END,
		     SD_TRANSFER_END);

	rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2, 0, 0);
	if (width == MMC_8BIT_BUS)
		rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + 1, 0, 0);

	retval = rtsx_send_cmd(chip, SD_CARD, 100);
	if (retval < 0) {
		rtsx_clear_sd_error(chip);
		return SWITCH_ERR;
	}

	ptr = rtsx_get_cmd_data(chip) + 1;

	if (width == MMC_8BIT_BUS) {
		dev_dbg(rtsx_dev(chip), "BUSTEST_R [8bits]: 0x%02x 0x%02x\n",
			ptr[0], ptr[1]);
		if ((ptr[0] == 0xAA) && (ptr[1] == 0x55)) {
			u8 rsp[5];
			u32 arg;

			if (CHK_MMC_DDR52(sd_card))
				arg = 0x03B70600;
			else
				arg = 0x03B70200;

			retval = sd_send_cmd_get_rsp(chip, SWITCH, arg,
						     SD_RSP_TYPE_R1b, rsp, 5);
			if ((retval == STATUS_SUCCESS) &&
			    !(rsp[4] & MMC_SWITCH_ERR))
				return SWITCH_SUCCESS;
		}
	} else {
		dev_dbg(rtsx_dev(chip), "BUSTEST_R [4bits]: 0x%02x\n", ptr[0]);
		if (ptr[0] == 0xA5) {
			u8 rsp[5];
			u32 arg;

			if (CHK_MMC_DDR52(sd_card))
				arg = 0x03B70500;
			else
				arg = 0x03B70100;

			retval = sd_send_cmd_get_rsp(chip, SWITCH, arg,
						     SD_RSP_TYPE_R1b, rsp, 5);
			if ((retval == STATUS_SUCCESS) &&
			    !(rsp[4] & MMC_SWITCH_ERR))
				return SWITCH_SUCCESS;
		}
	}

	return SWITCH_FAIL;
}