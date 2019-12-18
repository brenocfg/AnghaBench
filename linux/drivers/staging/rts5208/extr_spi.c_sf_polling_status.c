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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int /*<<< orphan*/  SPI_BUSY_ERR ; 
 int /*<<< orphan*/  SPI_COMMAND ; 
 int SPI_POLLING_MODE0 ; 
 int SPI_RDSR ; 
 int /*<<< orphan*/  SPI_TRANSFER0 ; 
 int SPI_TRANSFER0_END ; 
 int SPI_TRANSFER0_START ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_spi_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sf_polling_status(struct rtsx_chip *chip, int msec)
{
	int retval;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, SPI_RDSR);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_POLLING_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, msec);
	if (retval < 0) {
		rtsx_clear_spi_error(chip);
		spi_set_err_code(chip, SPI_BUSY_ERR);
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}