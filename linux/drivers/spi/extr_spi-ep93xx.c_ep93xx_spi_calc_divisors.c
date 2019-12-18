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
typedef  scalar_t__ u8 ;
typedef  unsigned long u32 ;
struct spi_master {int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  min_speed_hz; } ;
struct ep93xx_spi {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long clamp (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 struct ep93xx_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int ep93xx_spi_calc_divisors(struct spi_master *master,
				    u32 rate, u8 *div_cpsr, u8 *div_scr)
{
	struct ep93xx_spi *espi = spi_master_get_devdata(master);
	unsigned long spi_clk_rate = clk_get_rate(espi->clk);
	int cpsr, scr;

	/*
	 * Make sure that max value is between values supported by the
	 * controller.
	 */
	rate = clamp(rate, master->min_speed_hz, master->max_speed_hz);

	/*
	 * Calculate divisors so that we can get speed according the
	 * following formula:
	 *	rate = spi_clock_rate / (cpsr * (1 + scr))
	 *
	 * cpsr must be even number and starts from 2, scr can be any number
	 * between 0 and 255.
	 */
	for (cpsr = 2; cpsr <= 254; cpsr += 2) {
		for (scr = 0; scr <= 255; scr++) {
			if ((spi_clk_rate / (cpsr * (scr + 1))) <= rate) {
				*div_scr = (u8)scr;
				*div_cpsr = (u8)cpsr;
				return 0;
			}
		}
	}

	return -EINVAL;
}