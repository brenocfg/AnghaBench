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
typedef  int u32 ;
typedef  int u16 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {scalar_t__ ioaddr; } ;
struct pltfm_imx_data {TYPE_1__* socdata; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ESDHC_FLAG_MAN_TUNING ; 
 int ESDHC_FLAG_STD_TUNING ; 
 scalar_t__ ESDHC_MIX_CTRL ; 
 int ESDHC_MIX_CTRL_AC23EN ; 
 int ESDHC_MIX_CTRL_EXE_TUNE ; 
 int ESDHC_MIX_CTRL_SDHCI_MASK ; 
 int ESDHC_MIX_CTRL_SMPCLK_SEL ; 
 scalar_t__ ESDHC_VENDOR_SPEC ; 
 int ESDHC_VENDOR_SPEC_VSELECT ; 
 scalar_t__ SDHCI_AUTO_CMD_STATUS ; 
 int SDHCI_CTRL_EXEC_TUNING ; 
 int SDHCI_CTRL_PRESET_VAL_ENABLE ; 
 int SDHCI_CTRL_TUNED_CLK ; 
 int SDHCI_CTRL_VDD_180 ; 
 int SDHCI_HOST_CONTROL2 ; 
 int SDHCI_HOST_VERSION ; 
 int SDHCI_SPEC_300 ; 
 int SDHCI_TRANSFER_MODE ; 
 int SDHCI_TRNS_AUTO_CMD23 ; 
 scalar_t__ esdhc_is_usdhc (struct pltfm_imx_data*) ; 
 int readl (scalar_t__) ; 
 int readw (scalar_t__) ; 
 struct pltfm_imx_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 esdhc_readw_le(struct sdhci_host *host, int reg)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u16 ret = 0;
	u32 val;

	if (unlikely(reg == SDHCI_HOST_VERSION)) {
		reg ^= 2;
		if (esdhc_is_usdhc(imx_data)) {
			/*
			 * The usdhc register returns a wrong host version.
			 * Correct it here.
			 */
			return SDHCI_SPEC_300;
		}
	}

	if (unlikely(reg == SDHCI_HOST_CONTROL2)) {
		val = readl(host->ioaddr + ESDHC_VENDOR_SPEC);
		if (val & ESDHC_VENDOR_SPEC_VSELECT)
			ret |= SDHCI_CTRL_VDD_180;

		if (esdhc_is_usdhc(imx_data)) {
			if (imx_data->socdata->flags & ESDHC_FLAG_MAN_TUNING)
				val = readl(host->ioaddr + ESDHC_MIX_CTRL);
			else if (imx_data->socdata->flags & ESDHC_FLAG_STD_TUNING)
				/* the std tuning bits is in ACMD12_ERR for imx6sl */
				val = readl(host->ioaddr + SDHCI_AUTO_CMD_STATUS);
		}

		if (val & ESDHC_MIX_CTRL_EXE_TUNE)
			ret |= SDHCI_CTRL_EXEC_TUNING;
		if (val & ESDHC_MIX_CTRL_SMPCLK_SEL)
			ret |= SDHCI_CTRL_TUNED_CLK;

		ret &= ~SDHCI_CTRL_PRESET_VAL_ENABLE;

		return ret;
	}

	if (unlikely(reg == SDHCI_TRANSFER_MODE)) {
		if (esdhc_is_usdhc(imx_data)) {
			u32 m = readl(host->ioaddr + ESDHC_MIX_CTRL);
			ret = m & ESDHC_MIX_CTRL_SDHCI_MASK;
			/* Swap AC23 bit */
			if (m & ESDHC_MIX_CTRL_AC23EN) {
				ret &= ~ESDHC_MIX_CTRL_AC23EN;
				ret |= SDHCI_TRNS_AUTO_CMD23;
			}
		} else {
			ret = readw(host->ioaddr + SDHCI_TRANSFER_MODE);
		}

		return ret;
	}

	return readw(host->ioaddr + reg);
}