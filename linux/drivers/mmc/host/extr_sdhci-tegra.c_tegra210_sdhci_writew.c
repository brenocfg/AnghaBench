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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ MMC_SEND_TUNING_BLOCK ; 
 scalar_t__ MMC_SEND_TUNING_BLOCK_HS200 ; 
 int SDHCI_COMMAND ; 
 scalar_t__ SDHCI_GET_CMD (int /*<<< orphan*/ ) ; 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int) ; 
 int tegra_sdhci_configure_card_clk (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tegra210_sdhci_writew(struct sdhci_host *host, u16 val, int reg)
{
	bool is_tuning_cmd = 0;
	bool clk_enabled;
	u8 cmd;

	if (reg == SDHCI_COMMAND) {
		cmd = SDHCI_GET_CMD(val);
		is_tuning_cmd = cmd == MMC_SEND_TUNING_BLOCK ||
				cmd == MMC_SEND_TUNING_BLOCK_HS200;
	}

	if (is_tuning_cmd)
		clk_enabled = tegra_sdhci_configure_card_clk(host, 0);

	writew(val, host->ioaddr + reg);

	if (is_tuning_cmd) {
		udelay(1);
		sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
		tegra_sdhci_configure_card_clk(host, clk_enabled);
	}
}