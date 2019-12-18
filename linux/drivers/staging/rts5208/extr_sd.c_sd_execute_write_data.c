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
struct sd_info {int pre_cmd_err; int sd_lock_status; int last_rsp_type; int sd_addr; int sd_lock_notify; int /*<<< orphan*/  sd_erase_status; int /*<<< orphan*/ * rsp; int /*<<< orphan*/  sd_pass_thru_en; } ;
struct scsi_cmnd {int* cmnd; } ;
struct rtsx_chip {int card_ready; struct sd_info sd_card; } ;

/* Variables and functions */
 int APP_CMD ; 
 int CARD_DATA_SOURCE ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 scalar_t__ CHK_MMC_4BIT (struct sd_info*) ; 
 scalar_t__ CHK_MMC_8BIT (struct sd_info*) ; 
 scalar_t__ CHK_SD (struct sd_info*) ; 
 int /*<<< orphan*/  DMA_512 ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LOCK_UNLOCK ; 
 int PINGPONG_BUFFER ; 
 int PPBUF_BASE2 ; 
 int REG_SD_BLOCK_CNT_H ; 
 int REG_SD_BLOCK_CNT_L ; 
 int REG_SD_BYTE_CNT_H ; 
 int REG_SD_BYTE_CNT_L ; 
 int /*<<< orphan*/  REG_SD_CFG1 ; 
 int REG_SD_TRANSFER ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 int SD_BUS_WIDTH_4 ; 
 int SD_BUS_WIDTH_8 ; 
 int /*<<< orphan*/  SD_BYTE_CNT_H ; 
 int /*<<< orphan*/  SD_BYTE_CNT_L ; 
 int SD_CARD ; 
 int SD_CLR_PWD ; 
 int SD_ERASE ; 
 int SD_LOCKED ; 
 int SD_LOCK_1BIT_MODE ; 
 int SD_PWD_EXIST ; 
 int SD_RSP_TYPE_R1 ; 
 int SD_RSP_TYPE_R1b ; 
 int SD_SDR_RST ; 
 int SD_SET_PWD ; 
 int SD_TM_AUTO_WRITE_3 ; 
 int SD_TRANSFER_END ; 
 int SD_TRANSFER_START ; 
 int /*<<< orphan*/  SD_UNDER_ERASING ; 
 int SD_UNLOCK_POW_ON ; 
 int SEND_STATUS ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_CHANGE ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_NOT_PRESENT ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_WRITE_ERR ; 
 int /*<<< orphan*/  SENSE_TYPE_NO_SENSE ; 
 int SET_BLOCKLEN ; 
 int STATUS_SUCCESS ; 
 int STOP_TRANSMISSION ; 
 int TRANSPORT_ERROR ; 
 int TRANSPORT_FAILED ; 
 int TRANSPORT_GOOD ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_reset_sd_card (struct rtsx_chip*) ; 
 int ext_sd_send_cmd_get_rsp (struct rtsx_chip*,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 int get_rsp_type (struct scsi_cmnd*,int*,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sd_card (struct rtsx_chip*) ; 
 int reset_sd (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_sd_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int,int) ; 
 int /*<<< orphan*/  rtsx_send_cmd_no_wait (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_stor_get_xfer_buf (int*,int,struct scsi_cmnd*) ; 
 int rtsx_transfer_data (struct rtsx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 int sd_select_card (struct rtsx_chip*,int) ; 
 int sd_switch_clock (struct rtsx_chip*) ; 
 int sd_update_lock_status (struct rtsx_chip*) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trans_dma_enable (int /*<<< orphan*/ ,struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 

int sd_execute_write_data(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	unsigned int lun = SCSI_LUN(srb);
	int retval, rsp_len, i;
	bool write_err = false, cmd13_checkbit = false;
	u8 cmd_idx, rsp_type;
	bool standby = false, send_cmd12 = false, acmd = false;
	u32 data_len, arg;
#ifdef SUPPORT_SD_LOCK
	int lock_cmd_fail = 0;
	u8 sd_lock_state = 0;
	u8 lock_cmd_type = 0;
#endif

	if (!sd_card->sd_pass_thru_en) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	if (sd_card->pre_cmd_err) {
		sd_card->pre_cmd_err = 0;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		return TRANSPORT_FAILED;
	}

	retval = sd_switch_clock(chip);
	if (retval != STATUS_SUCCESS)
		return TRANSPORT_FAILED;

	cmd_idx = srb->cmnd[2] & 0x3F;
	if (srb->cmnd[1] & 0x04)
		send_cmd12 = true;

	if (srb->cmnd[1] & 0x02)
		standby = true;

	if (srb->cmnd[1] & 0x01)
		acmd = true;

	data_len = ((u32)srb->cmnd[7] << 16) | ((u32)srb->cmnd[8]
						<< 8) | srb->cmnd[9];
	arg = ((u32)srb->cmnd[3] << 24) | ((u32)srb->cmnd[4] << 16) |
		((u32)srb->cmnd[5] << 8) | srb->cmnd[6];

#ifdef SUPPORT_SD_LOCK
	if (cmd_idx == LOCK_UNLOCK) {
		sd_lock_state = sd_card->sd_lock_status;
		sd_lock_state &= SD_LOCKED;
	}
#endif

	retval = get_rsp_type(srb, &rsp_type, &rsp_len);
	if (retval != STATUS_SUCCESS) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}
	sd_card->last_rsp_type = rsp_type;

	retval = sd_switch_clock(chip);
	if (retval != STATUS_SUCCESS)
		return TRANSPORT_FAILED;

#ifdef SUPPORT_SD_LOCK
	if ((sd_card->sd_lock_status & SD_LOCK_1BIT_MODE) == 0) {
		if (CHK_MMC_8BIT(sd_card)) {
			retval = rtsx_write_register(chip, REG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_8);
			if (retval != STATUS_SUCCESS)
				return TRANSPORT_FAILED;

		} else if (CHK_SD(sd_card) || CHK_MMC_4BIT(sd_card)) {
			retval = rtsx_write_register(chip, REG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_4);
			if (retval != STATUS_SUCCESS)
				return TRANSPORT_FAILED;
		}
	}
#else
	retval = rtsx_write_register(chip, REG_SD_CFG1, 0x03, SD_BUS_WIDTH_4);
	if (retval != STATUS_SUCCESS)
		return TRANSPORT_FAILED;
#endif

	if (data_len < 512) {
		retval = ext_sd_send_cmd_get_rsp(chip, SET_BLOCKLEN, data_len,
						 SD_RSP_TYPE_R1, NULL, 0,
						 false);
		if (retval != STATUS_SUCCESS)
			goto sd_execute_write_cmd_failed;
	}

	if (standby) {
		retval = sd_select_card(chip, 0);
		if (retval != STATUS_SUCCESS)
			goto sd_execute_write_cmd_failed;
	}

	if (acmd) {
		retval = ext_sd_send_cmd_get_rsp(chip, APP_CMD,
						 sd_card->sd_addr,
						 SD_RSP_TYPE_R1, NULL, 0,
						 false);
		if (retval != STATUS_SUCCESS)
			goto sd_execute_write_cmd_failed;
	}

	retval = ext_sd_send_cmd_get_rsp(chip, cmd_idx, arg, rsp_type,
					 sd_card->rsp, rsp_len, false);
	if (retval != STATUS_SUCCESS)
		goto sd_execute_write_cmd_failed;

	if (data_len <= 512) {
		u16 i;
		u8 *buf;

		buf = kmalloc(data_len, GFP_KERNEL);
		if (!buf)
			return TRANSPORT_ERROR;

		rtsx_stor_get_xfer_buf(buf, data_len, srb);

#ifdef SUPPORT_SD_LOCK
		if (cmd_idx == LOCK_UNLOCK)
			lock_cmd_type = buf[0] & 0x0F;
#endif

		if (data_len > 256) {
			rtsx_init_cmd(chip);
			for (i = 0; i < 256; i++) {
				rtsx_add_cmd(chip, WRITE_REG_CMD,
					     PPBUF_BASE2 + i, 0xFF, buf[i]);
			}
			retval = rtsx_send_cmd(chip, 0, 250);
			if (retval != STATUS_SUCCESS) {
				kfree(buf);
				goto sd_execute_write_cmd_failed;
			}

			rtsx_init_cmd(chip);
			for (i = 256; i < data_len; i++) {
				rtsx_add_cmd(chip, WRITE_REG_CMD,
					     PPBUF_BASE2 + i, 0xFF, buf[i]);
			}
			retval = rtsx_send_cmd(chip, 0, 250);
			if (retval != STATUS_SUCCESS) {
				kfree(buf);
				goto sd_execute_write_cmd_failed;
			}
		} else {
			rtsx_init_cmd(chip);
			for (i = 0; i < data_len; i++) {
				rtsx_add_cmd(chip, WRITE_REG_CMD,
					     PPBUF_BASE2 + i, 0xFF, buf[i]);
			}
			retval = rtsx_send_cmd(chip, 0, 250);
			if (retval != STATUS_SUCCESS) {
				kfree(buf);
				goto sd_execute_write_cmd_failed;
			}
		}

		kfree(buf);

		rtsx_init_cmd(chip);

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF,
			     srb->cmnd[8] & 0x03);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF,
			     srb->cmnd[9]);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF,
			     0x00);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF,
			     0x01);
		rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01,
			     PINGPONG_BUFFER);

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
			     SD_TM_AUTO_WRITE_3 | SD_TRANSFER_START);
		rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER,
			     SD_TRANSFER_END, SD_TRANSFER_END);

		retval = rtsx_send_cmd(chip, SD_CARD, 250);
	} else if (!(data_len & 0x1FF)) {
		rtsx_init_cmd(chip);

		trans_dma_enable(DMA_TO_DEVICE, chip, data_len, DMA_512);

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF,
			     0x02);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF,
			     0x00);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H,
			     0xFF, (srb->cmnd[7] & 0xFE) >> 1);
		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L,
			     0xFF, (u8)((data_len & 0x0001FE00) >> 9));

		rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
			     SD_TM_AUTO_WRITE_3 | SD_TRANSFER_START);
		rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER,
			     SD_TRANSFER_END, SD_TRANSFER_END);

		rtsx_send_cmd_no_wait(chip);

		retval = rtsx_transfer_data(chip, SD_CARD, scsi_sglist(srb),
					    scsi_bufflen(srb),
					    scsi_sg_count(srb),
					    DMA_TO_DEVICE, 10000);

	} else {
		goto sd_execute_write_cmd_failed;
	}

	if (retval < 0) {
		write_err = true;
		rtsx_clear_sd_error(chip);
		goto sd_execute_write_cmd_failed;
	}

#ifdef SUPPORT_SD_LOCK
	if (cmd_idx == LOCK_UNLOCK) {
		if (lock_cmd_type == SD_ERASE) {
			sd_card->sd_erase_status = SD_UNDER_ERASING;
			scsi_set_resid(srb, 0);
			return TRANSPORT_GOOD;
		}

		rtsx_init_cmd(chip);
		rtsx_add_cmd(chip, CHECK_REG_CMD, 0xFD30, 0x02, 0x02);

		retval = rtsx_send_cmd(chip, SD_CARD, 250);
		if (retval < 0) {
			write_err = true;
			rtsx_clear_sd_error(chip);
			goto sd_execute_write_cmd_failed;
		}

		retval = sd_update_lock_status(chip);
		if (retval != STATUS_SUCCESS) {
			dev_dbg(rtsx_dev(chip), "Lock command fail!\n");
			lock_cmd_fail = 1;
		}
	}
#endif /* SUPPORT_SD_LOCK */

	if (standby) {
		retval = sd_select_card(chip, 1);
		if (retval != STATUS_SUCCESS)
			goto sd_execute_write_cmd_failed;
	}

	if (send_cmd12) {
		retval = ext_sd_send_cmd_get_rsp(chip, STOP_TRANSMISSION, 0,
						 SD_RSP_TYPE_R1b, NULL, 0,
						 false);
		if (retval != STATUS_SUCCESS)
			goto sd_execute_write_cmd_failed;
	}

	if (data_len < 512) {
		retval = ext_sd_send_cmd_get_rsp(chip, SET_BLOCKLEN, 0x200,
						 SD_RSP_TYPE_R1, NULL, 0,
						 false);
		if (retval != STATUS_SUCCESS)
			goto sd_execute_write_cmd_failed;

		retval = rtsx_write_register(chip, SD_BYTE_CNT_H, 0xFF, 0x02);
		if (retval != STATUS_SUCCESS)
			goto sd_execute_write_cmd_failed;

		retval = rtsx_write_register(chip, SD_BYTE_CNT_L, 0xFF, 0x00);
		if (retval != STATUS_SUCCESS)
			goto sd_execute_write_cmd_failed;
	}

	if ((srb->cmnd[1] & 0x02) || (srb->cmnd[1] & 0x04))
		cmd13_checkbit = true;

	for (i = 0; i < 3; i++) {
		retval = ext_sd_send_cmd_get_rsp(chip, SEND_STATUS,
						 sd_card->sd_addr,
						 SD_RSP_TYPE_R1, NULL, 0,
						 cmd13_checkbit);
		if (retval == STATUS_SUCCESS)
			break;
	}
	if (retval != STATUS_SUCCESS)
		goto sd_execute_write_cmd_failed;

#ifdef SUPPORT_SD_LOCK
	if (cmd_idx == LOCK_UNLOCK) {
		if (!lock_cmd_fail) {
			dev_dbg(rtsx_dev(chip), "lock_cmd_type = 0x%x\n",
				lock_cmd_type);
			if (lock_cmd_type & SD_CLR_PWD)
				sd_card->sd_lock_status &= ~SD_PWD_EXIST;

			if (lock_cmd_type & SD_SET_PWD)
				sd_card->sd_lock_status |= SD_PWD_EXIST;
		}

		dev_dbg(rtsx_dev(chip), "sd_lock_state = 0x%x, sd_card->sd_lock_status = 0x%x\n",
			sd_lock_state, sd_card->sd_lock_status);
		if (sd_lock_state ^ (sd_card->sd_lock_status & SD_LOCKED)) {
			sd_card->sd_lock_notify = 1;
			if (sd_lock_state &&
			    (sd_card->sd_lock_status & SD_LOCK_1BIT_MODE)) {
				sd_card->sd_lock_status |= (
					SD_UNLOCK_POW_ON | SD_SDR_RST);
				if (CHK_SD(sd_card)) {
					retval = reset_sd(chip);
					if (retval != STATUS_SUCCESS) {
						sd_card->sd_lock_status &= ~(SD_UNLOCK_POW_ON | SD_SDR_RST);
						goto sd_execute_write_cmd_failed;
					}
				}

				sd_card->sd_lock_status &= ~(SD_UNLOCK_POW_ON | SD_SDR_RST);
			}
		}
	}

	if (lock_cmd_fail) {
		scsi_set_resid(srb, 0);
		set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
		return TRANSPORT_FAILED;
	}
#endif  /* SUPPORT_SD_LOCK */

	scsi_set_resid(srb, 0);
	return TRANSPORT_GOOD;

sd_execute_write_cmd_failed:
	sd_card->pre_cmd_err = 1;
	set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
	if (write_err)
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_WRITE_ERR);

	release_sd_card(chip);
	do_reset_sd_card(chip);
	if (!(chip->card_ready & SD_CARD))
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);

	return TRANSPORT_FAILED;
}