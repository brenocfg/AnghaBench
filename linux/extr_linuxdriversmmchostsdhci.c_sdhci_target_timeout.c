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
struct sdhci_host {scalar_t__ clock; } ;
struct mmc_data {unsigned long long timeout_clks; int /*<<< orphan*/  timeout_ns; } ;
struct mmc_command {int busy_timeout; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ do_div (unsigned long long,scalar_t__) ; 

__attribute__((used)) static unsigned int sdhci_target_timeout(struct sdhci_host *host,
					 struct mmc_command *cmd,
					 struct mmc_data *data)
{
	unsigned int target_timeout;

	/* timeout in us */
	if (!data) {
		target_timeout = cmd->busy_timeout * 1000;
	} else {
		target_timeout = DIV_ROUND_UP(data->timeout_ns, 1000);
		if (host->clock && data->timeout_clks) {
			unsigned long long val;

			/*
			 * data->timeout_clks is in units of clock cycles.
			 * host->clock is in Hz.  target_timeout is in us.
			 * Hence, us = 1000000 * cycles / Hz.  Round up.
			 */
			val = 1000000ULL * data->timeout_clks;
			if (do_div(val, host->clock))
				target_timeout++;
			target_timeout += val;
		}
	}

	return target_timeout;
}