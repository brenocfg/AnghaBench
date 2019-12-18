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
struct mmc_ios {scalar_t__ power_mode; int /*<<< orphan*/  clock; int /*<<< orphan*/  bus_width; } ;
struct mmc_host {int dummy; } ;
struct alcor_sdmmc_host {scalar_t__ cur_power_mode; int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  alcor_set_bus_width (struct mmc_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  alcor_set_clock (struct alcor_sdmmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcor_set_power_mode (struct mmc_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  alcor_set_timing (struct mmc_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct alcor_sdmmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alcor_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct alcor_sdmmc_host *host = mmc_priv(mmc);

	mutex_lock(&host->cmd_mutex);

	dev_dbg(host->dev, "set ios. bus width: %x, power mode: %x\n",
		ios->bus_width, ios->power_mode);

	if (ios->power_mode != host->cur_power_mode) {
		alcor_set_power_mode(mmc, ios);
		host->cur_power_mode = ios->power_mode;
	} else {
		alcor_set_timing(mmc, ios);
		alcor_set_bus_width(mmc, ios);
		alcor_set_clock(host, ios->clock);
	}

	mutex_unlock(&host->cmd_mutex);
}