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
struct davinci_spi {int prescaler_limit; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int davinci_spi_get_prescale(struct davinci_spi *dspi,
							u32 max_speed_hz)
{
	int ret;

	/* Subtract 1 to match what will be programmed into SPI register. */
	ret = DIV_ROUND_UP(clk_get_rate(dspi->clk), max_speed_hz) - 1;

	if (ret < dspi->prescaler_limit || ret > 255)
		return -EINVAL;

	return ret;
}