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
struct spi_info {int clk_div; int /*<<< orphan*/  spi_clock; } ;
struct rtsx_chip {struct spi_info spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_CLK_EN ; 
 int /*<<< orphan*/  CARD_OE ; 
 int /*<<< orphan*/  SPI_CARD ; 
 int /*<<< orphan*/  SPI_CLK_DIVIDER0 ; 
 int /*<<< orphan*/  SPI_CLK_DIVIDER1 ; 
 int SPI_CLK_EN ; 
 int SPI_OUTPUT_EN ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int select_card (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int spi_init (struct rtsx_chip*) ; 
 int switch_clock (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int spi_set_init_para(struct rtsx_chip *chip)
{
	struct spi_info *spi = &chip->spi;
	int retval;

	retval = rtsx_write_register(chip, SPI_CLK_DIVIDER1, 0xFF,
				     (u8)(spi->clk_div >> 8));
	if (retval)
		return retval;
	retval = rtsx_write_register(chip, SPI_CLK_DIVIDER0, 0xFF,
				     (u8)(spi->clk_div));
	if (retval)
		return retval;

	retval = switch_clock(chip, spi->spi_clock);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = select_card(chip, SPI_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = rtsx_write_register(chip, CARD_CLK_EN, SPI_CLK_EN,
				     SPI_CLK_EN);
	if (retval)
		return retval;
	retval = rtsx_write_register(chip, CARD_OE, SPI_OUTPUT_EN,
				     SPI_OUTPUT_EN);
	if (retval)
		return retval;

	wait_timeout(10);

	retval = spi_init(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}