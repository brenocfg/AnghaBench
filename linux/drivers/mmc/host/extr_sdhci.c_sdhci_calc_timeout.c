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
typedef  int u8 ;
struct sdhci_host {int quirks; int timeout_clk; int quirks2; } ;
struct mmc_data {int dummy; } ;
struct mmc_command {int /*<<< orphan*/  opcode; int /*<<< orphan*/  busy_timeout; struct mmc_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ ) ; 
 int SDHCI_QUIRK2_DISABLE_HW_TIMEOUT ; 
 int SDHCI_QUIRK_BROKEN_TIMEOUT_VAL ; 
 unsigned int sdhci_target_timeout (struct sdhci_host*,struct mmc_command*,struct mmc_data*) ; 

__attribute__((used)) static u8 sdhci_calc_timeout(struct sdhci_host *host, struct mmc_command *cmd,
			     bool *too_big)
{
	u8 count;
	struct mmc_data *data;
	unsigned target_timeout, current_timeout;

	*too_big = true;

	/*
	 * If the host controller provides us with an incorrect timeout
	 * value, just skip the check and use 0xE.  The hardware may take
	 * longer to time out, but that's much better than having a too-short
	 * timeout value.
	 */
	if (host->quirks & SDHCI_QUIRK_BROKEN_TIMEOUT_VAL)
		return 0xE;

	/* Unspecified command, asume max */
	if (cmd == NULL)
		return 0xE;

	data = cmd->data;
	/* Unspecified timeout, assume max */
	if (!data && !cmd->busy_timeout)
		return 0xE;

	/* timeout in us */
	target_timeout = sdhci_target_timeout(host, cmd, data);

	/*
	 * Figure out needed cycles.
	 * We do this in steps in order to fit inside a 32 bit int.
	 * The first step is the minimum timeout, which will have a
	 * minimum resolution of 6 bits:
	 * (1) 2^13*1000 > 2^22,
	 * (2) host->timeout_clk < 2^16
	 *     =>
	 *     (1) / (2) > 2^6
	 */
	count = 0;
	current_timeout = (1 << 13) * 1000 / host->timeout_clk;
	while (current_timeout < target_timeout) {
		count++;
		current_timeout <<= 1;
		if (count >= 0xF)
			break;
	}

	if (count >= 0xF) {
		if (!(host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT))
			DBG("Too large timeout 0x%x requested for CMD%d!\n",
			    count, cmd->opcode);
		count = 0xE;
	} else {
		*too_big = false;
	}

	return count;
}