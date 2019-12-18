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
struct xtfpga_spi {int data; int data_sz; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTFPGA_SPI_DATA ; 
 int /*<<< orphan*/  XTFPGA_SPI_START ; 
 struct xtfpga_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtfpga_spi_wait_busy (struct xtfpga_spi*) ; 
 int /*<<< orphan*/  xtfpga_spi_write32 (struct xtfpga_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 xtfpga_spi_txrx_word(struct spi_device *spi, unsigned nsecs,
				u32 v, u8 bits, unsigned flags)
{
	struct xtfpga_spi *xspi = spi_master_get_devdata(spi->master);

	xspi->data = (xspi->data << bits) | (v & GENMASK(bits - 1, 0));
	xspi->data_sz += bits;
	if (xspi->data_sz >= 16) {
		xtfpga_spi_write32(xspi, XTFPGA_SPI_DATA,
				   xspi->data >> (xspi->data_sz - 16));
		xspi->data_sz -= 16;
		xtfpga_spi_write32(xspi, XTFPGA_SPI_START, 1);
		xtfpga_spi_wait_busy(xspi);
		xtfpga_spi_write32(xspi, XTFPGA_SPI_START, 0);
	}

	return 0;
}