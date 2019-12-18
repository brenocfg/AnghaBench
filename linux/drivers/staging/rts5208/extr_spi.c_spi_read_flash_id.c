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
typedef  int u16 ;
struct scsi_cmnd {int* cmnd; } ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DATA_SOURCE ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PINGPONG_BUFFER ; 
 int /*<<< orphan*/  SPI_ADDR0 ; 
 int /*<<< orphan*/  SPI_ADDR1 ; 
 int /*<<< orphan*/  SPI_ADDR2 ; 
 int SPI_ADDRESS_BIT_24 ; 
 int SPI_CADI_MODE0 ; 
 int SPI_CA_MODE0 ; 
 int /*<<< orphan*/  SPI_CA_NUMBER ; 
 int SPI_CDI_MODE0 ; 
 int /*<<< orphan*/  SPI_COMMAND ; 
 int SPI_COMMAND_BIT_8 ; 
 int SPI_C_MODE0 ; 
 int /*<<< orphan*/  SPI_HW_ERR ; 
 int /*<<< orphan*/  SPI_INVALID_COMMAND ; 
 int /*<<< orphan*/  SPI_LENGTH0 ; 
 int /*<<< orphan*/  SPI_LENGTH1 ; 
 int /*<<< orphan*/  SPI_NO_ERR ; 
 int /*<<< orphan*/  SPI_READ_ERR ; 
 int /*<<< orphan*/  SPI_TRANSFER0 ; 
 int SPI_TRANSFER0_END ; 
 int SPI_TRANSFER0_START ; 
 int STATUS_ERROR ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_spi_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_read_ppbuf (struct rtsx_chip*,int /*<<< orphan*/ *,int) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtsx_stor_set_xfer_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int spi_set_init_para (struct rtsx_chip*) ; 

int spi_read_flash_id(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	int retval;
	u16 len;
	u8 *buf;

	spi_set_err_code(chip, SPI_NO_ERR);

	len = ((u16)(srb->cmnd[7]) << 8) | srb->cmnd[8];
	if (len > 512) {
		spi_set_err_code(chip, SPI_INVALID_COMMAND);
		return STATUS_FAIL;
	}

	retval = spi_set_init_para(chip);
	if (retval != STATUS_SUCCESS) {
		spi_set_err_code(chip, SPI_HW_ERR);
		return STATUS_FAIL;
	}

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01,
		     PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, srb->cmnd[3]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR2, 0xFF, srb->cmnd[4]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF, srb->cmnd[5]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR0, 0xFF, srb->cmnd[6]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH1, 0xFF, srb->cmnd[7]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH0, 0xFF, srb->cmnd[8]);

	if (len == 0) {
		if (srb->cmnd[9]) {
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0,
				     0xFF, SPI_TRANSFER0_START | SPI_CA_MODE0);
		} else {
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0,
				     0xFF, SPI_TRANSFER0_START | SPI_C_MODE0);
		}
	} else {
		if (srb->cmnd[9]) {
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
				     SPI_TRANSFER0_START | SPI_CADI_MODE0);
		} else {
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
				     SPI_TRANSFER0_START | SPI_CDI_MODE0);
		}
	}

	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	if (retval < 0) {
		rtsx_clear_spi_error(chip);
		spi_set_err_code(chip, SPI_HW_ERR);
		return STATUS_FAIL;
	}

	if (len) {
		buf = kmalloc(len, GFP_KERNEL);
		if (!buf)
			return STATUS_ERROR;

		retval = rtsx_read_ppbuf(chip, buf, len);
		if (retval != STATUS_SUCCESS) {
			spi_set_err_code(chip, SPI_READ_ERR);
			kfree(buf);
			return STATUS_FAIL;
		}

		rtsx_stor_set_xfer_buf(buf, scsi_bufflen(srb), srb);
		scsi_set_resid(srb, 0);

		kfree(buf);
	}

	return STATUS_SUCCESS;
}