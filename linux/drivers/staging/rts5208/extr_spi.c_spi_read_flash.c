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
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int /*<<< orphan*/  DMA_256 ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SF_PAGE_LEN ; 
 int /*<<< orphan*/  SPI_ADDR0 ; 
 int /*<<< orphan*/  SPI_ADDR1 ; 
 int /*<<< orphan*/  SPI_ADDR2 ; 
 int /*<<< orphan*/  SPI_ADDR3 ; 
 int SPI_ADDRESS_BIT_24 ; 
 int SPI_ADDRESS_BIT_32 ; 
 int SPI_CADI_MODE0 ; 
 int /*<<< orphan*/  SPI_CA_NUMBER ; 
 int /*<<< orphan*/  SPI_COMMAND ; 
 int SPI_COMMAND_BIT_8 ; 
 int /*<<< orphan*/  SPI_HW_ERR ; 
 int /*<<< orphan*/  SPI_LENGTH0 ; 
 int /*<<< orphan*/  SPI_LENGTH1 ; 
 int /*<<< orphan*/  SPI_NO_ERR ; 
 int /*<<< orphan*/  SPI_TRANSFER0 ; 
 int SPI_TRANSFER0_END ; 
 int SPI_TRANSFER0_START ; 
 int STATUS_ERROR ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TO_XFER_BUF ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_spi_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_send_cmd_no_wait (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_stor_access_xfer_buf (int*,int,struct scsi_cmnd*,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int rtsx_transfer_data (struct rtsx_chip*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int spi_set_init_para (struct rtsx_chip*) ; 
 int /*<<< orphan*/  trans_dma_enable (int /*<<< orphan*/ ,struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 

int spi_read_flash(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	int retval;
	unsigned int index = 0, offset = 0;
	u8 ins, slow_read;
	u32 addr;
	u16 len;
	u8 *buf;

	spi_set_err_code(chip, SPI_NO_ERR);

	ins = srb->cmnd[3];
	addr = ((u32)(srb->cmnd[4]) << 16) | ((u32)(srb->cmnd[5])
					<< 8) | srb->cmnd[6];
	len = ((u16)(srb->cmnd[7]) << 8) | srb->cmnd[8];
	slow_read = srb->cmnd[9];

	retval = spi_set_init_para(chip);
	if (retval != STATUS_SUCCESS) {
		spi_set_err_code(chip, SPI_HW_ERR);
		return STATUS_FAIL;
	}

	buf = kmalloc(SF_PAGE_LEN, GFP_KERNEL);
	if (!buf)
		return STATUS_ERROR;

	while (len) {
		u16 pagelen = SF_PAGE_LEN - (u8)addr;

		if (pagelen > len)
			pagelen = len;

		rtsx_init_cmd(chip);

		trans_dma_enable(DMA_FROM_DEVICE, chip, 256, DMA_256);

		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, ins);

		if (slow_read) {
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR0, 0xFF,
				     (u8)addr);
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF,
				     (u8)(addr >> 8));
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR2, 0xFF,
				     (u8)(addr >> 16));
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
				     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
		} else {
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF,
				     (u8)addr);
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR2, 0xFF,
				     (u8)(addr >> 8));
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR3, 0xFF,
				     (u8)(addr >> 16));
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
				     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_32);
		}

		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH1, 0xFF,
			     (u8)(pagelen >> 8));
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH0, 0xFF,
			     (u8)pagelen);

		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
			     SPI_TRANSFER0_START | SPI_CADI_MODE0);
		rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0,
			     SPI_TRANSFER0_END, SPI_TRANSFER0_END);

		rtsx_send_cmd_no_wait(chip);

		retval = rtsx_transfer_data(chip, 0, buf, pagelen, 0,
					    DMA_FROM_DEVICE, 10000);
		if (retval < 0) {
			kfree(buf);
			rtsx_clear_spi_error(chip);
			spi_set_err_code(chip, SPI_HW_ERR);
			return STATUS_FAIL;
		}

		rtsx_stor_access_xfer_buf(buf, pagelen, srb, &index, &offset,
					  TO_XFER_BUF);

		addr += pagelen;
		len -= pagelen;
	}

	scsi_set_resid(srb, 0);
	kfree(buf);

	return STATUS_SUCCESS;
}