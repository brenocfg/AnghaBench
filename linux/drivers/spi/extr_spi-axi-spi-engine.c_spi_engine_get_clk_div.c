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
struct spi_transfer {int speed_hz; } ;
struct spi_engine {int /*<<< orphan*/  ref_clk; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int spi_engine_get_clk_div(struct spi_engine *spi_engine,
	struct spi_device *spi, struct spi_transfer *xfer)
{
	unsigned int clk_div;

	clk_div = DIV_ROUND_UP(clk_get_rate(spi_engine->ref_clk),
		xfer->speed_hz * 2);
	if (clk_div > 255)
		clk_div = 255;
	else if (clk_div > 0)
		clk_div -= 1;

	return clk_div;
}