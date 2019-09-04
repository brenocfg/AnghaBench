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
struct sdhci_pltfm_host {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ SYSCTL_CLKD_MAX ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 sdhci_omap_calc_divisor(struct sdhci_pltfm_host *host,
				   unsigned int clock)
{
	u16 dsor;

	dsor = DIV_ROUND_UP(clk_get_rate(host->clk), clock);
	if (dsor > SYSCTL_CLKD_MAX)
		dsor = SYSCTL_CLKD_MAX;

	return dsor;
}