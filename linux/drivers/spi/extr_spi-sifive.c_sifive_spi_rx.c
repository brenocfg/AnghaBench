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
struct sifive_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIFIVE_SPI_REG_RXDATA ; 
 int SIFIVE_SPI_RXDATA_DATA_MASK ; 
 int SIFIVE_SPI_RXDATA_EMPTY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int sifive_spi_read (struct sifive_spi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sifive_spi_rx(struct sifive_spi *spi, u8 *rx_ptr)
{
	u32 data = sifive_spi_read(spi, SIFIVE_SPI_REG_RXDATA);

	WARN_ON_ONCE((data & SIFIVE_SPI_RXDATA_EMPTY) != 0);
	*rx_ptr = data & SIFIVE_SPI_RXDATA_DATA_MASK;
}