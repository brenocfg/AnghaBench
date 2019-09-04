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
typedef  scalar_t__ u16 ;
struct omap_hsmmc_host {int /*<<< orphan*/  fclk; } ;
struct mmc_ios {scalar_t__ clock; } ;

/* Variables and functions */
 scalar_t__ CLKD_MAX ; 
 scalar_t__ DIV_ROUND_UP (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 calc_divisor(struct omap_hsmmc_host *host, struct mmc_ios *ios)
{
	u16 dsor = 0;

	if (ios->clock) {
		dsor = DIV_ROUND_UP(clk_get_rate(host->fclk), ios->clock);
		if (dsor > CLKD_MAX)
			dsor = CLKD_MAX;
	}

	return dsor;
}