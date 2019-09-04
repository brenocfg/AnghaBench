#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct pcan_pccard {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int PCC_EEP_RDSR ; 
 int PCC_EEP_SR_WEN ; 
 int PCC_EEP_SR_WIP ; 
 int PCC_EEP_WRDI ; 
 int PCC_EEP_WREN ; 
 int PCC_EEP_WRITE (int) ; 
 int /*<<< orphan*/  PCC_SPI_ADR ; 
 int /*<<< orphan*/  PCC_SPI_DIR ; 
 int /*<<< orphan*/  PCC_SPI_DOR ; 
 int /*<<< orphan*/  PCC_SPI_IR ; 
 int PCC_WRITE_MAX_LOOP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int pcan_read_reg (struct pcan_pccard*,int /*<<< orphan*/ ) ; 
 int pcan_wait_spi_busy (struct pcan_pccard*) ; 
 int /*<<< orphan*/  pcan_write_reg (struct pcan_pccard*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcan_write_eeprom(struct pcan_pccard *card, u16 addr, u8 v)
{
	u8 status;
	int err, i;

	/* write instruction enabling write */
	pcan_write_reg(card, PCC_SPI_IR, PCC_EEP_WREN);
	err = pcan_wait_spi_busy(card);
	if (err)
		goto we_spi_err;

	/* wait until write enabled */
	for (i = 0; i < PCC_WRITE_MAX_LOOP; i++) {
		/* write instruction reading the status register */
		pcan_write_reg(card, PCC_SPI_IR, PCC_EEP_RDSR);
		err = pcan_wait_spi_busy(card);
		if (err)
			goto we_spi_err;

		/* get status register value and check write enable bit */
		status = pcan_read_reg(card, PCC_SPI_DIR);
		if (status & PCC_EEP_SR_WEN)
			break;
	}

	if (i >= PCC_WRITE_MAX_LOOP) {
		dev_err(&card->pdev->dev,
			"stop waiting to be allowed to write in eeprom\n");
		return -EIO;
	}

	/* set address and data */
	pcan_write_reg(card, PCC_SPI_ADR, addr & 0xff);
	pcan_write_reg(card, PCC_SPI_DOR, v);

	/*
	 * write instruction with bit[3] set according to address value:
	 * if addr refers to upper half of the memory array: bit[3] = 1
	 */
	pcan_write_reg(card, PCC_SPI_IR, PCC_EEP_WRITE(addr));
	err = pcan_wait_spi_busy(card);
	if (err)
		goto we_spi_err;

	/* wait while write in progress */
	for (i = 0; i < PCC_WRITE_MAX_LOOP; i++) {
		/* write instruction reading the status register */
		pcan_write_reg(card, PCC_SPI_IR, PCC_EEP_RDSR);
		err = pcan_wait_spi_busy(card);
		if (err)
			goto we_spi_err;

		/* get status register value and check write in progress bit */
		status = pcan_read_reg(card, PCC_SPI_DIR);
		if (!(status & PCC_EEP_SR_WIP))
			break;
	}

	if (i >= PCC_WRITE_MAX_LOOP) {
		dev_err(&card->pdev->dev,
			"stop waiting for write in eeprom to complete\n");
		return -EIO;
	}

	/* write instruction disabling write */
	pcan_write_reg(card, PCC_SPI_IR, PCC_EEP_WRDI);
	err = pcan_wait_spi_busy(card);
	if (err)
		goto we_spi_err;

	return 0;

we_spi_err:
	dev_err(&card->pdev->dev,
		"stop waiting (spi engine always busy) err %d\n", err);

	return err;
}