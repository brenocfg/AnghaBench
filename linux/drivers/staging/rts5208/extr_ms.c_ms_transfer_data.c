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
struct rtsx_chip {int /*<<< orphan*/  mspro_timeout; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int /*<<< orphan*/  DMA_512 ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int ETIMEDOUT ; 
 int MS_2K_SECTOR_MODE ; 
 int /*<<< orphan*/  MS_CARD ; 
 int /*<<< orphan*/  MS_CFG ; 
 int MS_CRC16_ERR ; 
 int MS_FLASH_READ_ERROR ; 
 int MS_FLASH_WRITE_ERROR ; 
 int MS_INT_CMDNK ; 
 int MS_INT_ERR ; 
 int MS_RDY_TIMEOUT ; 
 int /*<<< orphan*/  MS_SECTOR_CNT_H ; 
 int /*<<< orphan*/  MS_SECTOR_CNT_L ; 
 int MS_TM_AUTO_READ ; 
 int MS_TM_AUTO_WRITE ; 
 int /*<<< orphan*/  MS_TPC ; 
 int /*<<< orphan*/  MS_TRANSFER ; 
 int MS_TRANSFER_END ; 
 int MS_TRANSFER_START ; 
 int /*<<< orphan*/  MS_TRANS_CFG ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int STATUS_TIMEDOUT ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  ms_set_err_code (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtsx_send_cmd_no_wait (struct rtsx_chip*) ; 
 int rtsx_transfer_data (struct rtsx_chip*,int /*<<< orphan*/ ,void*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trans_dma_enable (int,struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms_transfer_data(struct rtsx_chip *chip, u8 trans_mode,
			    u8 tpc, u16 sec_cnt, u8 cfg, bool mode_2k,
			    int use_sg, void *buf, int buf_len)
{
	int retval;
	u8 val, err_code = 0;
	enum dma_data_direction dir;

	if (!buf || !buf_len)
		return STATUS_FAIL;

	if (trans_mode == MS_TM_AUTO_READ) {
		dir = DMA_FROM_DEVICE;
		err_code = MS_FLASH_READ_ERROR;
	} else if (trans_mode == MS_TM_AUTO_WRITE) {
		dir = DMA_TO_DEVICE;
		err_code = MS_FLASH_WRITE_ERROR;
	} else {
		return STATUS_FAIL;
	}

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_add_cmd(chip, WRITE_REG_CMD,
		     MS_SECTOR_CNT_H, 0xFF, (u8)(sec_cnt >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_SECTOR_CNT_L, 0xFF, (u8)sec_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);

	if (mode_2k) {
		rtsx_add_cmd(chip, WRITE_REG_CMD,
			     MS_CFG, MS_2K_SECTOR_MODE, MS_2K_SECTOR_MODE);
	} else {
		rtsx_add_cmd(chip, WRITE_REG_CMD, MS_CFG, MS_2K_SECTOR_MODE, 0);
	}

	trans_dma_enable(dir, chip, sec_cnt * 512, DMA_512);

	rtsx_add_cmd(chip, WRITE_REG_CMD,
		     MS_TRANSFER, 0xFF, MS_TRANSFER_START | trans_mode);
	rtsx_add_cmd(chip, CHECK_REG_CMD,
		     MS_TRANSFER, MS_TRANSFER_END, MS_TRANSFER_END);

	rtsx_send_cmd_no_wait(chip);

	retval = rtsx_transfer_data(chip, MS_CARD, buf, buf_len,
				    use_sg, dir, chip->mspro_timeout);
	if (retval < 0) {
		ms_set_err_code(chip, err_code);
		if (retval == -ETIMEDOUT)
			retval = STATUS_TIMEDOUT;
		else
			retval = STATUS_FAIL;

		return retval;
	}

	retval = rtsx_read_register(chip, MS_TRANS_CFG, &val);
	if (retval)
		return retval;

	if (val & (MS_INT_CMDNK | MS_INT_ERR | MS_CRC16_ERR | MS_RDY_TIMEOUT))
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}