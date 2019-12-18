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
typedef  int /*<<< orphan*/  u32 ;
struct a3700_spi {unsigned int byte_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  A3700_SPI_BYTE_LEN ; 
 int /*<<< orphan*/  A3700_SPI_IF_CFG_REG ; 
 int /*<<< orphan*/  spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a3700_spi_bytelen_set(struct a3700_spi *a3700_spi, unsigned int len)
{
	u32 val;

	val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
	if (len == 4)
		val |= A3700_SPI_BYTE_LEN;
	else
		val &= ~A3700_SPI_BYTE_LEN;
	spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	a3700_spi->byte_len = len;
}