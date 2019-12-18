#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct jz4740_mmc_host {scalar_t__ base; int /*<<< orphan*/  clk; TYPE_1__* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_max; } ;

/* Variables and functions */
 scalar_t__ JZ_REG_MMC_CLKRT ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_mmc_clock_disable (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int jz4740_mmc_set_clock_rate(struct jz4740_mmc_host *host, int rate)
{
	int div = 0;
	int real_rate;

	jz4740_mmc_clock_disable(host);
	clk_set_rate(host->clk, host->mmc->f_max);

	real_rate = clk_get_rate(host->clk);

	while (real_rate > rate && div < 7) {
		++div;
		real_rate >>= 1;
	}

	writew(div, host->base + JZ_REG_MMC_CLKRT);
	return real_rate;
}