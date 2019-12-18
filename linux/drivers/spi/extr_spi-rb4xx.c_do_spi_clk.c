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
struct rb4xx_spi {int dummy; } ;

/* Variables and functions */
 int AR71XX_SPI_IOC_CLK ; 
 int AR71XX_SPI_IOC_DO ; 
 int /*<<< orphan*/  AR71XX_SPI_REG_IOC ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb4xx_write (struct rb4xx_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void do_spi_clk(struct rb4xx_spi *rbspi, u32 spi_ioc, int value)
{
	u32 regval;

	regval = spi_ioc;
	if (value & BIT(0))
		regval |= AR71XX_SPI_IOC_DO;

	rb4xx_write(rbspi, AR71XX_SPI_REG_IOC, regval);
	rb4xx_write(rbspi, AR71XX_SPI_REG_IOC, regval | AR71XX_SPI_IOC_CLK);
}