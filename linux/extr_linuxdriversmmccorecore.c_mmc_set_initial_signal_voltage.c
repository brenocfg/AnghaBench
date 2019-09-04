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
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_SIGNAL_VOLTAGE_120 ; 
 int /*<<< orphan*/  MMC_SIGNAL_VOLTAGE_180 ; 
 int /*<<< orphan*/  MMC_SIGNAL_VOLTAGE_330 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_signal_voltage (struct mmc_host*,int /*<<< orphan*/ ) ; 

void mmc_set_initial_signal_voltage(struct mmc_host *host)
{
	/* Try to set signal voltage to 3.3V but fall back to 1.8v or 1.2v */
	if (!mmc_set_signal_voltage(host, MMC_SIGNAL_VOLTAGE_330))
		dev_dbg(mmc_dev(host), "Initial signal voltage of 3.3v\n");
	else if (!mmc_set_signal_voltage(host, MMC_SIGNAL_VOLTAGE_180))
		dev_dbg(mmc_dev(host), "Initial signal voltage of 1.8v\n");
	else if (!mmc_set_signal_voltage(host, MMC_SIGNAL_VOLTAGE_120))
		dev_dbg(mmc_dev(host), "Initial signal voltage of 1.2v\n");
}