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
typedef  int u32 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int KS_SPIOP_RD ; 
 int SPI_ADDR_MASK ; 
 int SPI_ADDR_SHIFT ; 
 int SPI_TURNAROUND_SHIFT ; 
 int cpu_to_be32 (int) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int ksz_spi_read_reg(struct spi_device *spi, u32 reg, u8 *val,
			    unsigned int len)
{
	u32 txbuf;
	int ret;

	txbuf = reg & SPI_ADDR_MASK;
	txbuf |= KS_SPIOP_RD << SPI_ADDR_SHIFT;
	txbuf <<= SPI_TURNAROUND_SHIFT;
	txbuf = cpu_to_be32(txbuf);

	ret = spi_write_then_read(spi, &txbuf, 4, val, len);
	return ret;
}