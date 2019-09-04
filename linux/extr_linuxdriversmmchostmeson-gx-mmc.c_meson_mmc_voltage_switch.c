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
struct mmc_ios {scalar_t__ signal_voltage; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MMC_SIGNAL_VOLTAGE_330 ; 
 int mmc_regulator_set_vqmmc (struct mmc_host*,struct mmc_ios*) ; 

__attribute__((used)) static int meson_mmc_voltage_switch(struct mmc_host *mmc, struct mmc_ios *ios)
{
	/* vqmmc regulator is available */
	if (!IS_ERR(mmc->supply.vqmmc)) {
		/*
		 * The usual amlogic setup uses a GPIO to switch from one
		 * regulator to the other. While the voltage ramp up is
		 * pretty fast, care must be taken when switching from 3.3v
		 * to 1.8v. Please make sure the regulator framework is aware
		 * of your own regulator constraints
		 */
		return mmc_regulator_set_vqmmc(mmc, ios);
	}

	/* no vqmmc regulator, assume fixed regulator at 3/3.3V */
	if (ios->signal_voltage == MMC_SIGNAL_VOLTAGE_330)
		return 0;

	return -EINVAL;
}