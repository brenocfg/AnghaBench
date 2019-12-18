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
struct scsi_cmnd {int* cmnd; } ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int AAI_PROGRAM ; 
 int BYTE_PROGRAM ; 
 int /*<<< orphan*/  CARD_DATA_SOURCE ; 
 int /*<<< orphan*/  DMA_256 ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FROM_XFER_BUF ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_PROGRAM ; 
 int PINGPONG_BUFFER ; 
 int /*<<< orphan*/  PPBUF_BASE2 ; 
 int SF_PAGE_LEN ; 
 int /*<<< orphan*/  SPI_HW_ERR ; 
 int /*<<< orphan*/  SPI_INVALID_COMMAND ; 
 int /*<<< orphan*/  SPI_NO_ERR ; 
 int /*<<< orphan*/  SPI_WRDI ; 
 int /*<<< orphan*/  SPI_WREN ; 
 int STATUS_ERROR ; 
 int STATUS_FAIL ; 
 int STATUS_NOMEM ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_spi_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtsx_send_cmd_no_wait (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_stor_access_xfer_buf (int*,int,struct scsi_cmnd*,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int rtsx_transfer_data (struct rtsx_chip*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sf_disable_write (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sf_enable_write (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sf_polling_status (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  sf_program (struct rtsx_chip*,int,int,int,int) ; 
 int /*<<< orphan*/  spi_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int spi_set_init_para (struct rtsx_chip*) ; 
 int /*<<< orphan*/  trans_dma_enable (int /*<<< orphan*/ ,struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 

int spi_write_flash(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	int retval;
	u8 ins, program_mode;
	u32 addr;
	u16 len;
	u8 *buf;
	unsigned int index = 0, offset = 0;

	spi_set_err_code(chip, SPI_NO_ERR);

	ins = srb->cmnd[3];
	addr = ((u32)(srb->cmnd[4]) << 16) | ((u32)(srb->cmnd[5])
					<< 8) | srb->cmnd[6];
	len = ((u16)(srb->cmnd[7]) << 8) | srb->cmnd[8];
	program_mode = srb->cmnd[9];

	retval = spi_set_init_para(chip);
	if (retval != STATUS_SUCCESS) {
		spi_set_err_code(chip, SPI_HW_ERR);
		return STATUS_FAIL;
	}

	if (program_mode == BYTE_PROGRAM) {
		buf = kmalloc(4, GFP_KERNEL);
		if (!buf)
			return STATUS_ERROR;

		while (len) {
			retval = sf_enable_write(chip, SPI_WREN);
			if (retval != STATUS_SUCCESS) {
				kfree(buf);
				return STATUS_FAIL;
			}

			rtsx_stor_access_xfer_buf(buf, 1, srb, &index, &offset,
						  FROM_XFER_BUF);

			rtsx_init_cmd(chip);

			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
				     0x01, PINGPONG_BUFFER);
			rtsx_add_cmd(chip, WRITE_REG_CMD, PPBUF_BASE2, 0xFF,
				     buf[0]);
			sf_program(chip, ins, 1, addr, 1);

			retval = rtsx_send_cmd(chip, 0, 100);
			if (retval < 0) {
				kfree(buf);
				rtsx_clear_spi_error(chip);
				spi_set_err_code(chip, SPI_HW_ERR);
				return STATUS_FAIL;
			}

			retval = sf_polling_status(chip, 100);
			if (retval != STATUS_SUCCESS) {
				kfree(buf);
				return STATUS_FAIL;
			}

			addr++;
			len--;
		}

		kfree(buf);

	} else if (program_mode == AAI_PROGRAM) {
		int first_byte = 1;

		retval = sf_enable_write(chip, SPI_WREN);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		buf = kmalloc(4, GFP_KERNEL);
		if (!buf)
			return STATUS_ERROR;

		while (len) {
			rtsx_stor_access_xfer_buf(buf, 1, srb, &index, &offset,
						  FROM_XFER_BUF);

			rtsx_init_cmd(chip);

			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
				     0x01, PINGPONG_BUFFER);
			rtsx_add_cmd(chip, WRITE_REG_CMD, PPBUF_BASE2, 0xFF,
				     buf[0]);
			if (first_byte) {
				sf_program(chip, ins, 1, addr, 1);
				first_byte = 0;
			} else {
				sf_program(chip, ins, 0, 0, 1);
			}

			retval = rtsx_send_cmd(chip, 0, 100);
			if (retval < 0) {
				kfree(buf);
				rtsx_clear_spi_error(chip);
				spi_set_err_code(chip, SPI_HW_ERR);
				return STATUS_FAIL;
			}

			retval = sf_polling_status(chip, 100);
			if (retval != STATUS_SUCCESS) {
				kfree(buf);
				return STATUS_FAIL;
			}

			len--;
		}

		kfree(buf);

		retval = sf_disable_write(chip, SPI_WRDI);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		retval = sf_polling_status(chip, 100);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;
	} else if (program_mode == PAGE_PROGRAM) {
		buf = kmalloc(SF_PAGE_LEN, GFP_KERNEL);
		if (!buf)
			return STATUS_NOMEM;

		while (len) {
			u16 pagelen = SF_PAGE_LEN - (u8)addr;

			if (pagelen > len)
				pagelen = len;

			retval = sf_enable_write(chip, SPI_WREN);
			if (retval != STATUS_SUCCESS) {
				kfree(buf);
				return STATUS_FAIL;
			}

			rtsx_init_cmd(chip);

			trans_dma_enable(DMA_TO_DEVICE, chip, 256, DMA_256);
			sf_program(chip, ins, 1, addr, pagelen);

			rtsx_send_cmd_no_wait(chip);

			rtsx_stor_access_xfer_buf(buf, pagelen, srb, &index,
						  &offset, FROM_XFER_BUF);

			retval = rtsx_transfer_data(chip, 0, buf, pagelen, 0,
						    DMA_TO_DEVICE, 100);
			if (retval < 0) {
				kfree(buf);
				rtsx_clear_spi_error(chip);
				spi_set_err_code(chip, SPI_HW_ERR);
				return STATUS_FAIL;
			}

			retval = sf_polling_status(chip, 100);
			if (retval != STATUS_SUCCESS) {
				kfree(buf);
				return STATUS_FAIL;
			}

			addr += pagelen;
			len -= pagelen;
		}

		kfree(buf);
	} else {
		spi_set_err_code(chip, SPI_INVALID_COMMAND);
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}