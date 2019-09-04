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
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {scalar_t__ ioaddr; } ;
struct pltfm_imx_data {TYPE_1__* socdata; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ESDHC_FLAG_MAN_TUNING ; 
 int ESDHC_FLAG_STD_TUNING ; 
 scalar_t__ ESDHC_MIX_CTRL ; 
 int /*<<< orphan*/  ESDHC_MIX_CTRL_FBCLK_SEL ; 
 int /*<<< orphan*/  ESDHC_MIX_CTRL_SMPCLK_SEL ; 
 scalar_t__ ESDHC_TUNE_CTRL_STATUS ; 
 scalar_t__ SDHCI_AUTO_CMD_STATUS ; 
 scalar_t__ esdhc_is_usdhc (struct pltfm_imx_data*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct pltfm_imx_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void esdhc_reset_tuning(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u32 ctrl;

	/* Reset the tuning circuit */
	if (esdhc_is_usdhc(imx_data)) {
		if (imx_data->socdata->flags & ESDHC_FLAG_MAN_TUNING) {
			ctrl = readl(host->ioaddr + ESDHC_MIX_CTRL);
			ctrl &= ~ESDHC_MIX_CTRL_SMPCLK_SEL;
			ctrl &= ~ESDHC_MIX_CTRL_FBCLK_SEL;
			writel(ctrl, host->ioaddr + ESDHC_MIX_CTRL);
			writel(0, host->ioaddr + ESDHC_TUNE_CTRL_STATUS);
		} else if (imx_data->socdata->flags & ESDHC_FLAG_STD_TUNING) {
			ctrl = readl(host->ioaddr + SDHCI_AUTO_CMD_STATUS);
			ctrl &= ~ESDHC_MIX_CTRL_SMPCLK_SEL;
			writel(ctrl, host->ioaddr + SDHCI_AUTO_CMD_STATUS);
		}
	}
}