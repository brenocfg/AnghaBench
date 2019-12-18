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
typedef  int u32 ;
struct zynq_qspi {int /*<<< orphan*/  refclk; } ;
struct spi_device {int max_speed_hz; int mode; } ;

/* Variables and functions */
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int ZYNQ_QSPI_BAUD_DIV_MAX ; 
 int ZYNQ_QSPI_BAUD_DIV_SHIFT ; 
 int ZYNQ_QSPI_CONFIG_BDRATE_MASK ; 
 int ZYNQ_QSPI_CONFIG_CPHA_MASK ; 
 int ZYNQ_QSPI_CONFIG_CPOL_MASK ; 
 int /*<<< orphan*/  ZYNQ_QSPI_CONFIG_OFFSET ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int zynq_qspi_read (struct zynq_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_qspi_write (struct zynq_qspi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zynq_qspi_config_op(struct zynq_qspi *xqspi, struct spi_device *spi)
{
	u32 config_reg, baud_rate_val = 0;

	/*
	 * Set the clock frequency
	 * The baud rate divisor is not a direct mapping to the value written
	 * into the configuration register (config_reg[5:3])
	 * i.e. 000 - divide by 2
	 *      001 - divide by 4
	 *      ----------------
	 *      111 - divide by 256
	 */
	while ((baud_rate_val < ZYNQ_QSPI_BAUD_DIV_MAX)  &&
	       (clk_get_rate(xqspi->refclk) / (2 << baud_rate_val)) >
		spi->max_speed_hz)
		baud_rate_val++;

	config_reg = zynq_qspi_read(xqspi, ZYNQ_QSPI_CONFIG_OFFSET);

	/* Set the QSPI clock phase and clock polarity */
	config_reg &= (~ZYNQ_QSPI_CONFIG_CPHA_MASK) &
		      (~ZYNQ_QSPI_CONFIG_CPOL_MASK);
	if (spi->mode & SPI_CPHA)
		config_reg |= ZYNQ_QSPI_CONFIG_CPHA_MASK;
	if (spi->mode & SPI_CPOL)
		config_reg |= ZYNQ_QSPI_CONFIG_CPOL_MASK;

	config_reg &= ~ZYNQ_QSPI_CONFIG_BDRATE_MASK;
	config_reg |= (baud_rate_val << ZYNQ_QSPI_BAUD_DIV_SHIFT);
	zynq_qspi_write(xqspi, ZYNQ_QSPI_CONFIG_OFFSET, config_reg);

	return 0;
}