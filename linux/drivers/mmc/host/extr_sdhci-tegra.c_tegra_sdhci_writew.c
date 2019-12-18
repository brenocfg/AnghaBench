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
typedef  int u16 ;
struct sdhci_pltfm_host {int xfer_mode_shadow; } ;
struct sdhci_host {int const ioaddr; } ;

/* Variables and functions */
#define  SDHCI_COMMAND 129 
#define  SDHCI_TRANSFER_MODE 128 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  writel (int,int const) ; 
 int /*<<< orphan*/  writew (int,int const) ; 

__attribute__((used)) static void tegra_sdhci_writew(struct sdhci_host *host, u16 val, int reg)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	switch (reg) {
	case SDHCI_TRANSFER_MODE:
		/*
		 * Postpone this write, we must do it together with a
		 * command write that is down below.
		 */
		pltfm_host->xfer_mode_shadow = val;
		return;
	case SDHCI_COMMAND:
		writel((val << 16) | pltfm_host->xfer_mode_shadow,
			host->ioaddr + SDHCI_TRANSFER_MODE);
		return;
	}

	writew(val, host->ioaddr + reg);
}