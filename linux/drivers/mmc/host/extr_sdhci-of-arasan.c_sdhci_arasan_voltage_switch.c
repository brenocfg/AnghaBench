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
struct mmc_ios {int signal_voltage; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MMC_SIGNAL_VOLTAGE_120 130 
#define  MMC_SIGNAL_VOLTAGE_180 129 
#define  MMC_SIGNAL_VOLTAGE_330 128 

__attribute__((used)) static int sdhci_arasan_voltage_switch(struct mmc_host *mmc,
				       struct mmc_ios *ios)
{
	switch (ios->signal_voltage) {
	case MMC_SIGNAL_VOLTAGE_180:
		/*
		 * Plese don't switch to 1V8 as arasan,5.1 doesn't
		 * actually refer to this setting to indicate the
		 * signal voltage and the state machine will be broken
		 * actually if we force to enable 1V8. That's something
		 * like broken quirk but we could work around here.
		 */
		return 0;
	case MMC_SIGNAL_VOLTAGE_330:
	case MMC_SIGNAL_VOLTAGE_120:
		/* We don't support 3V3 and 1V2 */
		break;
	}

	return -EINVAL;
}