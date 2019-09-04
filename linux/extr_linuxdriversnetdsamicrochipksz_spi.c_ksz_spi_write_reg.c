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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int KS_SPIOP_WR ; 
 int SPI_ADDR_MASK ; 
 int SPI_ADDR_SHIFT ; 
 int SPI_TURNAROUND_SHIFT ; 
 int cpu_to_be32 (int) ; 
 int spi_write (struct spi_device*,int**,int) ; 

__attribute__((used)) static int ksz_spi_write_reg(struct spi_device *spi, u32 reg, u8 *val,
			     unsigned int len)
{
	u32 txbuf;
	u8 data[12];
	int i;

	txbuf = reg & SPI_ADDR_MASK;
	txbuf |= (KS_SPIOP_WR << SPI_ADDR_SHIFT);
	txbuf <<= SPI_TURNAROUND_SHIFT;
	txbuf = cpu_to_be32(txbuf);

	data[0] = txbuf & 0xFF;
	data[1] = (txbuf & 0xFF00) >> 8;
	data[2] = (txbuf & 0xFF0000) >> 16;
	data[3] = (txbuf & 0xFF000000) >> 24;
	for (i = 0; i < len; i++)
		data[i + 4] = val[i];

	return spi_write(spi, &data, 4 + len);
}