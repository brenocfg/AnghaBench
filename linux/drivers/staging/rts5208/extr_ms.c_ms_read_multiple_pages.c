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
struct ms_info {int dummy; } ;
struct rtsx_chip {int card_wp; int /*<<< orphan*/  srb; int /*<<< orphan*/  ms_timeout; struct ms_info ms_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_END ; 
 int /*<<< orphan*/  BLOCK_READ ; 
 int /*<<< orphan*/  CARD_DATA_SOURCE ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 scalar_t__ CHK_MS4BIT (struct ms_info*) ; 
 int /*<<< orphan*/  DMA_512 ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GET_INT ; 
 int INT_REG_BREQ ; 
 int INT_REG_CED ; 
 int INT_REG_CMDNK ; 
 int INT_REG_ERR ; 
 int /*<<< orphan*/  MS_BREQ_ERROR ; 
 int MS_CARD ; 
 int /*<<< orphan*/  MS_CMD_NK ; 
 int MS_CRC16_ERR ; 
 int /*<<< orphan*/  MS_CRC16_ERROR ; 
 int MS_EXTRA_SIZE ; 
 int /*<<< orphan*/  MS_FLASH_READ_ERROR ; 
 int MS_MAX_RETRY_COUNT ; 
 int /*<<< orphan*/  MS_NO_CARD ; 
 int /*<<< orphan*/  MS_NO_ERROR ; 
 int MS_RDY_TIMEOUT ; 
 int MS_TM_NORMAL_READ ; 
 int /*<<< orphan*/  MS_TO_ERROR ; 
 int /*<<< orphan*/  MS_TPC ; 
 int /*<<< orphan*/  MS_TRANSFER ; 
 int MS_TRANSFER_END ; 
 int MS_TRANSFER_START ; 
 int /*<<< orphan*/  MS_TRANS_CFG ; 
 int NO_WAIT_INT ; 
 int /*<<< orphan*/  OverwriteFlag ; 
 int READ_PAGE_DATA ; 
 int RING_BUFFER ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int STATUS_TIMEDOUT ; 
 int /*<<< orphan*/  SystemParm ; 
 int WAIT_INT ; 
 int /*<<< orphan*/  WRITE_REG ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int detect_card_cd (struct rtsx_chip*,int) ; 
 int ms_read_bytes (struct rtsx_chip*,int /*<<< orphan*/ ,int,int,int*,int) ; 
 int ms_read_extra_data (struct rtsx_chip*,int,int,int*,int) ; 
 int ms_read_status_reg (struct rtsx_chip*) ; 
 int ms_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ms_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_set_page_status (int,int /*<<< orphan*/ ,int*,int) ; 
 int ms_set_rw_reg_addr (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int ms_write_bytes (struct rtsx_chip*,int /*<<< orphan*/ ,int,int,int*,int) ; 
 int /*<<< orphan*/  ms_write_extra_data (struct rtsx_chip*,int,int,int*,int) ; 
 int /*<<< orphan*/  reset_ms (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_ms_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtsx_send_cmd_no_wait (struct rtsx_chip*) ; 
 int rtsx_transfer_data_partial (struct rtsx_chip*,int,int*,int,scalar_t__,unsigned int*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_sg_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setPS_NG ; 
 int /*<<< orphan*/  trans_dma_enable (int /*<<< orphan*/ ,struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms_read_multiple_pages(struct rtsx_chip *chip, u16 phy_blk,
				  u16 log_blk, u8 start_page, u8 end_page,
				  u8 *buf, unsigned int *index,
				  unsigned int *offset)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval, i;
	u8 extra[MS_EXTRA_SIZE], page_addr, val, trans_cfg, data[6];
	u8 *ptr;

	retval = ms_read_extra_data(chip, phy_blk, start_page,
				    extra, MS_EXTRA_SIZE);
	if (retval == STATUS_SUCCESS) {
		if ((extra[1] & 0x30) != 0x30) {
			ms_set_err_code(chip, MS_FLASH_READ_ERROR);
			return STATUS_FAIL;
		}
	}

	retval = ms_set_rw_reg_addr(chip, OverwriteFlag, MS_EXTRA_SIZE,
				    SystemParm, 6);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	if (CHK_MS4BIT(ms_card))
		data[0] = 0x88;
	else
		data[0] = 0x80;

	data[1] = 0;
	data[2] = (u8)(phy_blk >> 8);
	data[3] = (u8)phy_blk;
	data[4] = 0;
	data[5] = start_page;

	for (i = 0; i < MS_MAX_RETRY_COUNT; i++) {
		retval = ms_write_bytes(chip, WRITE_REG, 6, NO_WAIT_INT,
					data, 6);
		if (retval == STATUS_SUCCESS)
			break;
	}
	if (i == MS_MAX_RETRY_COUNT)
		return STATUS_FAIL;

	ms_set_err_code(chip, MS_NO_ERROR);

	retval = ms_send_cmd(chip, BLOCK_READ, WAIT_INT);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	ptr = buf;

	for (page_addr = start_page; page_addr < end_page; page_addr++) {
		ms_set_err_code(chip, MS_NO_ERROR);

		if (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) {
			ms_set_err_code(chip, MS_NO_CARD);
			return STATUS_FAIL;
		}

		retval = ms_read_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		if (val & INT_REG_CMDNK) {
			ms_set_err_code(chip, MS_CMD_NK);
			return STATUS_FAIL;
		}
		if (val & INT_REG_ERR) {
			if (val & INT_REG_BREQ) {
				retval = ms_read_status_reg(chip);
				if (retval != STATUS_SUCCESS) {
					if (!(chip->card_wp & MS_CARD)) {
						reset_ms(chip);
						ms_set_page_status
							(log_blk, setPS_NG,
							 extra,
							 MS_EXTRA_SIZE);
						ms_write_extra_data
							(chip, phy_blk,
							 page_addr, extra,
							 MS_EXTRA_SIZE);
					}
					ms_set_err_code(chip,
							MS_FLASH_READ_ERROR);
					return STATUS_FAIL;
				}
			} else {
				ms_set_err_code(chip, MS_FLASH_READ_ERROR);
				return STATUS_FAIL;
			}
		} else {
			if (!(val & INT_REG_BREQ)) {
				ms_set_err_code(chip, MS_BREQ_ERROR);
				return STATUS_FAIL;
			}
		}

		if (page_addr == (end_page - 1)) {
			if (!(val & INT_REG_CED)) {
				retval = ms_send_cmd(chip, BLOCK_END, WAIT_INT);
				if (retval != STATUS_SUCCESS)
					return STATUS_FAIL;
			}

			retval = ms_read_bytes(chip, GET_INT, 1, NO_WAIT_INT,
					       &val, 1);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;

			if (!(val & INT_REG_CED)) {
				ms_set_err_code(chip, MS_FLASH_READ_ERROR);
				return STATUS_FAIL;
			}

			trans_cfg = NO_WAIT_INT;
		} else {
			trans_cfg = WAIT_INT;
		}

		rtsx_init_cmd(chip);

		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC, 0xFF, READ_PAGE_DATA);
		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG,
			     0xFF, trans_cfg);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
			     0x01, RING_BUFFER);

		trans_dma_enable(DMA_FROM_DEVICE, chip, 512, DMA_512);

		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANSFER, 0xFF,
			     MS_TRANSFER_START |  MS_TM_NORMAL_READ);
		rtsx_add_cmd(chip, CHECK_REG_CMD, MS_TRANSFER,
			     MS_TRANSFER_END, MS_TRANSFER_END);

		rtsx_send_cmd_no_wait(chip);

		retval = rtsx_transfer_data_partial(chip, MS_CARD, ptr, 512,
						    scsi_sg_count(chip->srb),
						    index, offset,
						    DMA_FROM_DEVICE,
						    chip->ms_timeout);
		if (retval < 0) {
			if (retval == -ETIMEDOUT) {
				ms_set_err_code(chip, MS_TO_ERROR);
				rtsx_clear_ms_error(chip);
				return STATUS_TIMEDOUT;
			}

			retval = rtsx_read_register(chip, MS_TRANS_CFG, &val);
			if (retval != STATUS_SUCCESS) {
				ms_set_err_code(chip, MS_TO_ERROR);
				rtsx_clear_ms_error(chip);
				return STATUS_TIMEDOUT;
			}
			if (val & (MS_CRC16_ERR | MS_RDY_TIMEOUT)) {
				ms_set_err_code(chip, MS_CRC16_ERROR);
				rtsx_clear_ms_error(chip);
				return STATUS_FAIL;
			}
		}

		if (scsi_sg_count(chip->srb) == 0)
			ptr += 512;
	}

	return STATUS_SUCCESS;
}