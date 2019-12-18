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
struct stm32_spi {int clk_rate; int cur_speed; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int fls (int) ; 

__attribute__((used)) static int stm32_spi_prepare_mbr(struct stm32_spi *spi, u32 speed_hz,
				 u32 min_div, u32 max_div)
{
	u32 div, mbrdiv;

	div = DIV_ROUND_UP(spi->clk_rate, speed_hz);

	/*
	 * SPI framework set xfer->speed_hz to master->max_speed_hz if
	 * xfer->speed_hz is greater than master->max_speed_hz, and it returns
	 * an error when xfer->speed_hz is lower than master->min_speed_hz, so
	 * no need to check it there.
	 * However, we need to ensure the following calculations.
	 */
	if ((div < min_div) || (div > max_div))
		return -EINVAL;

	/* Determine the first power of 2 greater than or equal to div */
	if (div & (div - 1))
		mbrdiv = fls(div);
	else
		mbrdiv = fls(div) - 1;

	spi->cur_speed = spi->clk_rate / (1 << mbrdiv);

	return mbrdiv - 1;
}