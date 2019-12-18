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
typedef  int u64 ;
struct sdhci_host {unsigned int clock; int data_timeout; struct mmc_host* mmc; } ;
struct mmc_ios {int bus_width; } ;
struct mmc_host {scalar_t__ actual_clock; struct mmc_ios ios; } ;
struct mmc_data {unsigned int blksz; int blocks; } ;
struct mmc_command {struct mmc_data* data; } ;

/* Variables and functions */
 scalar_t__ MMC_CMD_TRANSFER_TIME ; 
 int NSEC_PER_SEC ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 
 int sdhci_target_timeout (struct sdhci_host*,struct mmc_command*,struct mmc_data*) ; 

__attribute__((used)) static void sdhci_calc_sw_timeout(struct sdhci_host *host,
				  struct mmc_command *cmd)
{
	struct mmc_data *data = cmd->data;
	struct mmc_host *mmc = host->mmc;
	struct mmc_ios *ios = &mmc->ios;
	unsigned char bus_width = 1 << ios->bus_width;
	unsigned int blksz;
	unsigned int freq;
	u64 target_timeout;
	u64 transfer_time;

	target_timeout = sdhci_target_timeout(host, cmd, data);
	target_timeout *= NSEC_PER_USEC;

	if (data) {
		blksz = data->blksz;
		freq = host->mmc->actual_clock ? : host->clock;
		transfer_time = (u64)blksz * NSEC_PER_SEC * (8 / bus_width);
		do_div(transfer_time, freq);
		/* multiply by '2' to account for any unknowns */
		transfer_time = transfer_time * 2;
		/* calculate timeout for the entire data */
		host->data_timeout = data->blocks * target_timeout +
				     transfer_time;
	} else {
		host->data_timeout = target_timeout;
	}

	if (host->data_timeout)
		host->data_timeout += MMC_CMD_TRANSFER_TIME;
}