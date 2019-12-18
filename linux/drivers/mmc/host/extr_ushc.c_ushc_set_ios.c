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
struct ushc_data {int dummy; } ;
struct mmc_ios {int bus_width; scalar_t__ timing; int /*<<< orphan*/  clock; int /*<<< orphan*/  power_mode; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ MMC_TIMING_SD_HS ; 
 struct ushc_data* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  ushc_set_bus_freq (struct ushc_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ushc_set_bus_width (struct ushc_data*,int) ; 
 int /*<<< orphan*/  ushc_set_power (struct ushc_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ushc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct ushc_data *ushc = mmc_priv(mmc);

	ushc_set_power(ushc, ios->power_mode);
	ushc_set_bus_width(ushc, 1 << ios->bus_width);
	ushc_set_bus_freq(ushc, ios->clock, ios->timing == MMC_TIMING_SD_HS);
}