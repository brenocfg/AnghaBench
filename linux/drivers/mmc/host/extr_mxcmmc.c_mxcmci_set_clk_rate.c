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
struct mxcmci_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  clk_per; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_REG_CLK_RATE ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxcmci_writew (struct mxcmci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxcmci_set_clk_rate(struct mxcmci_host *host, unsigned int clk_ios)
{
	unsigned int divider;
	int prescaler = 0;
	unsigned int clk_in = clk_get_rate(host->clk_per);

	while (prescaler <= 0x800) {
		for (divider = 1; divider <= 0xF; divider++) {
			int x;

			x = (clk_in / (divider + 1));

			if (prescaler)
				x /= (prescaler * 2);

			if (x <= clk_ios)
				break;
		}
		if (divider < 0x10)
			break;

		if (prescaler == 0)
			prescaler = 1;
		else
			prescaler <<= 1;
	}

	mxcmci_writew(host, (prescaler << 4) | divider, MMC_REG_CLK_RATE);

	dev_dbg(mmc_dev(host->mmc), "scaler: %d divider: %d in: %d out: %d\n",
			prescaler, divider, clk_in, clk_ios);
}