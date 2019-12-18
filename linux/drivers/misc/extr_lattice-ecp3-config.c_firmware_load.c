#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct fpga_data {int /*<<< orphan*/  fw_loaded; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {scalar_t__ jedec_id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int FPGA_CLEAR_LOOP_COUNT ; 
 int /*<<< orphan*/  FPGA_CLEAR_MSLEEP ; 
 int FPGA_CMD_CLEAR ; 
 int FPGA_CMD_READ_ID ; 
 int FPGA_CMD_READ_STATUS ; 
 int FPGA_CMD_REFRESH ; 
 int FPGA_CMD_WRITE_DIS ; 
 int FPGA_CMD_WRITE_EN ; 
 int FPGA_CMD_WRITE_INC ; 
 scalar_t__ FPGA_STATUS_CLEARED ; 
 scalar_t__ FPGA_STATUS_DONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* ecp3_dev ; 
 scalar_t__ get_unaligned_be32 (int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 struct fpga_data* spi_get_drvdata (struct spi_device*) ; 
 int spi_write (struct spi_device*,int*,int) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int*,int) ; 

__attribute__((used)) static void firmware_load(const struct firmware *fw, void *context)
{
	struct spi_device *spi = (struct spi_device *)context;
	struct fpga_data *data = spi_get_drvdata(spi);
	u8 *buffer;
	int ret;
	u8 txbuf[8];
	u8 rxbuf[8];
	int rx_len = 8;
	int i;
	u32 jedec_id;
	u32 status;

	if (fw == NULL) {
		dev_err(&spi->dev, "Cannot load firmware, aborting\n");
		return;
	}

	if (fw->size == 0) {
		dev_err(&spi->dev, "Error: Firmware size is 0!\n");
		return;
	}

	/* Fill dummy data (24 stuffing bits for commands) */
	txbuf[1] = 0x00;
	txbuf[2] = 0x00;
	txbuf[3] = 0x00;

	/* Trying to speak with the FPGA via SPI... */
	txbuf[0] = FPGA_CMD_READ_ID;
	ret = spi_write_then_read(spi, txbuf, 8, rxbuf, rx_len);
	jedec_id = get_unaligned_be32(&rxbuf[4]);
	dev_dbg(&spi->dev, "FPGA JTAG ID=%08x\n", jedec_id);

	for (i = 0; i < ARRAY_SIZE(ecp3_dev); i++) {
		if (jedec_id == ecp3_dev[i].jedec_id)
			break;
	}
	if (i == ARRAY_SIZE(ecp3_dev)) {
		dev_err(&spi->dev,
			"Error: No supported FPGA detected (JEDEC_ID=%08x)!\n",
			jedec_id);
		return;
	}

	dev_info(&spi->dev, "FPGA %s detected\n", ecp3_dev[i].name);

	txbuf[0] = FPGA_CMD_READ_STATUS;
	ret = spi_write_then_read(spi, txbuf, 8, rxbuf, rx_len);
	status = get_unaligned_be32(&rxbuf[4]);
	dev_dbg(&spi->dev, "FPGA Status=%08x\n", status);

	buffer = kzalloc(fw->size + 8, GFP_KERNEL);
	if (!buffer) {
		dev_err(&spi->dev, "Error: Can't allocate memory!\n");
		return;
	}

	/*
	 * Insert WRITE_INC command into stream (one SPI frame)
	 */
	buffer[0] = FPGA_CMD_WRITE_INC;
	buffer[1] = 0xff;
	buffer[2] = 0xff;
	buffer[3] = 0xff;
	memcpy(buffer + 4, fw->data, fw->size);

	txbuf[0] = FPGA_CMD_REFRESH;
	ret = spi_write(spi, txbuf, 4);

	txbuf[0] = FPGA_CMD_WRITE_EN;
	ret = spi_write(spi, txbuf, 4);

	txbuf[0] = FPGA_CMD_CLEAR;
	ret = spi_write(spi, txbuf, 4);

	/*
	 * Wait for FPGA memory to become cleared
	 */
	for (i = 0; i < FPGA_CLEAR_LOOP_COUNT; i++) {
		txbuf[0] = FPGA_CMD_READ_STATUS;
		ret = spi_write_then_read(spi, txbuf, 8, rxbuf, rx_len);
		status = get_unaligned_be32(&rxbuf[4]);
		if (status == FPGA_STATUS_CLEARED)
			break;

		msleep(FPGA_CLEAR_MSLEEP);
	}

	if (i == FPGA_CLEAR_LOOP_COUNT) {
		dev_err(&spi->dev,
			"Error: Timeout waiting for FPGA to clear (status=%08x)!\n",
			status);
		kfree(buffer);
		return;
	}

	dev_info(&spi->dev, "Configuring the FPGA...\n");
	ret = spi_write(spi, buffer, fw->size + 8);

	txbuf[0] = FPGA_CMD_WRITE_DIS;
	ret = spi_write(spi, txbuf, 4);

	txbuf[0] = FPGA_CMD_READ_STATUS;
	ret = spi_write_then_read(spi, txbuf, 8, rxbuf, rx_len);
	status = get_unaligned_be32(&rxbuf[4]);
	dev_dbg(&spi->dev, "FPGA Status=%08x\n", status);

	/* Check result */
	if (status & FPGA_STATUS_DONE)
		dev_info(&spi->dev, "FPGA successfully configured!\n");
	else
		dev_info(&spi->dev, "FPGA not configured (DONE not set)\n");

	/*
	 * Don't forget to release the firmware again
	 */
	release_firmware(fw);

	kfree(buffer);

	complete(&data->fw_loaded);
}