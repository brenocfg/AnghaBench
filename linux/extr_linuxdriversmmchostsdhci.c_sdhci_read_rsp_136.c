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
struct sdhci_host {int quirks2; } ;
struct mmc_command {int* resp; } ;

/* Variables and functions */
 int SDHCI_QUIRK2_RSP_136_HAS_CRC ; 
 int SDHCI_RESPONSE ; 
 int sdhci_readl (struct sdhci_host*,int) ; 

__attribute__((used)) static void sdhci_read_rsp_136(struct sdhci_host *host, struct mmc_command *cmd)
{
	int i, reg;

	for (i = 0; i < 4; i++) {
		reg = SDHCI_RESPONSE + (3 - i) * 4;
		cmd->resp[i] = sdhci_readl(host, reg);
	}

	if (host->quirks2 & SDHCI_QUIRK2_RSP_136_HAS_CRC)
		return;

	/* CRC is stripped so we need to do some shifting */
	for (i = 0; i < 4; i++) {
		cmd->resp[i] <<= 8;
		if (i != 3)
			cmd->resp[i] |= cmd->resp[i + 1] >> 24;
	}
}