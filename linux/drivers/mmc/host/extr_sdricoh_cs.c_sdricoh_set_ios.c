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
struct sdricoh_host {int /*<<< orphan*/  dev; } ;
struct mmc_ios {scalar_t__ power_mode; scalar_t__ bus_width; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_POWER_ON ; 
 scalar_t__ MMC_POWER_UP ; 
 int /*<<< orphan*/  R224_MODE ; 
 int /*<<< orphan*/  R228_POWER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct sdricoh_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sdricoh_writel (struct sdricoh_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sdricoh_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct sdricoh_host *host = mmc_priv(mmc);
	dev_dbg(host->dev, "set_ios\n");

	if (ios->power_mode == MMC_POWER_ON) {
		sdricoh_writel(host, R228_POWER, 0xc0e0);

		if (ios->bus_width == MMC_BUS_WIDTH_4) {
			sdricoh_writel(host, R224_MODE, 0x2000300);
			sdricoh_writel(host, R228_POWER, 0x40e0);
		} else {
			sdricoh_writel(host, R224_MODE, 0x2000340);
		}

	} else if (ios->power_mode == MMC_POWER_UP) {
		sdricoh_writel(host, R224_MODE, 0x2000320);
		sdricoh_writel(host, R228_POWER, 0xe0);
	}
}