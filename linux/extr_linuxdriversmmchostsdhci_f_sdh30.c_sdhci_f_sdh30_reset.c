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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_host {int dummy; } ;
struct f_sdhost_priv {scalar_t__ enable_cmd_dat_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SDH30_CMD_DAT_DELAY ; 
 int /*<<< orphan*/  F_SDH30_ESD_CONTROL ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 struct f_sdhost_priv* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_f_sdh30_reset(struct sdhci_host *host, u8 mask)
{
	struct f_sdhost_priv *priv = sdhci_priv(host);
	u32 ctl;

	if (sdhci_readw(host, SDHCI_CLOCK_CONTROL) == 0)
		sdhci_writew(host, 0xBC01, SDHCI_CLOCK_CONTROL);

	sdhci_reset(host, mask);

	if (priv->enable_cmd_dat_delay) {
		ctl = sdhci_readl(host, F_SDH30_ESD_CONTROL);
		ctl |= F_SDH30_CMD_DAT_DELAY;
		sdhci_writel(host, ctl, F_SDH30_ESD_CONTROL);
	}
}