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
struct a3700_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A3700_SPI_AUTO_CS ; 
 int /*<<< orphan*/  A3700_SPI_IF_CFG_REG ; 
 int /*<<< orphan*/  spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a3700_spi_auto_cs_unset(struct a3700_spi *a3700_spi)
{
	u32 val;

	val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
	val &= ~A3700_SPI_AUTO_CS;
	spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);
}