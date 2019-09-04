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
typedef  int u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {scalar_t__ ioaddr; } ;
struct pltfm_imx_data {scalar_t__ is_ddr; } ;

/* Variables and functions */
 int ESDHC_CTRL_BUSWIDTH_MASK ; 
 int ESDHC_CTRL_D3CD ; 
 int ESDHC_HOST_CONTROL_LE ; 
 scalar_t__ ESDHC_MIX_CTRL ; 
 int ESDHC_MIX_CTRL_TUNING_MASK ; 
 int const ESDHC_SYSTEM_CONTROL ; 
 int SDHCI_CTRL_DMA_MASK ; 
 int SDHCI_CTRL_LED ; 
#define  SDHCI_HOST_CONTROL 130 
#define  SDHCI_POWER_CONTROL 129 
 int SDHCI_RESET_ALL ; 
 int SDHCI_RESET_DATA ; 
#define  SDHCI_SOFTWARE_RESET 128 
 int /*<<< orphan*/  esdhc_clrset_le (struct sdhci_host*,int,int,int const) ; 
 scalar_t__ esdhc_is_usdhc (struct pltfm_imx_data*) ; 
 int /*<<< orphan*/  is_imx25_esdhc (struct pltfm_imx_data*) ; 
 int readl (scalar_t__) ; 
 struct pltfm_imx_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void esdhc_writeb_le(struct sdhci_host *host, u8 val, int reg)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u32 new_val = 0;
	u32 mask;

	switch (reg) {
	case SDHCI_POWER_CONTROL:
		/*
		 * FSL put some DMA bits here
		 * If your board has a regulator, code should be here
		 */
		return;
	case SDHCI_HOST_CONTROL:
		/* FSL messed up here, so we need to manually compose it. */
		new_val = val & SDHCI_CTRL_LED;
		/* ensure the endianness */
		new_val |= ESDHC_HOST_CONTROL_LE;
		/* bits 8&9 are reserved on mx25 */
		if (!is_imx25_esdhc(imx_data)) {
			/* DMA mode bits are shifted */
			new_val |= (val & SDHCI_CTRL_DMA_MASK) << 5;
		}

		/*
		 * Do not touch buswidth bits here. This is done in
		 * esdhc_pltfm_bus_width.
		 * Do not touch the D3CD bit either which is used for the
		 * SDIO interrupt erratum workaround.
		 */
		mask = 0xffff & ~(ESDHC_CTRL_BUSWIDTH_MASK | ESDHC_CTRL_D3CD);

		esdhc_clrset_le(host, mask, new_val, reg);
		return;
	case SDHCI_SOFTWARE_RESET:
		if (val & SDHCI_RESET_DATA)
			new_val = readl(host->ioaddr + SDHCI_HOST_CONTROL);
		break;
	}
	esdhc_clrset_le(host, 0xff, val, reg);

	if (reg == SDHCI_SOFTWARE_RESET) {
		if (val & SDHCI_RESET_ALL) {
			/*
			 * The esdhc has a design violation to SDHC spec which
			 * tells that software reset should not affect card
			 * detection circuit. But esdhc clears its SYSCTL
			 * register bits [0..2] during the software reset. This
			 * will stop those clocks that card detection circuit
			 * relies on. To work around it, we turn the clocks on
			 * back to keep card detection circuit functional.
			 */
			esdhc_clrset_le(host, 0x7, 0x7, ESDHC_SYSTEM_CONTROL);
			/*
			 * The reset on usdhc fails to clear MIX_CTRL register.
			 * Do it manually here.
			 */
			if (esdhc_is_usdhc(imx_data)) {
				/*
				 * the tuning bits should be kept during reset
				 */
				new_val = readl(host->ioaddr + ESDHC_MIX_CTRL);
				writel(new_val & ESDHC_MIX_CTRL_TUNING_MASK,
						host->ioaddr + ESDHC_MIX_CTRL);
				imx_data->is_ddr = 0;
			}
		} else if (val & SDHCI_RESET_DATA) {
			/*
			 * The eSDHC DAT line software reset clears at least the
			 * data transfer width on i.MX25, so make sure that the
			 * Host Control register is unaffected.
			 */
			esdhc_clrset_le(host, 0xff, new_val,
					SDHCI_HOST_CONTROL);
		}
	}
}