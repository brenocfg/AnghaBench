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
struct sdhci_tegra_soc_data {int nvquirks; } ;
struct sdhci_tegra {struct sdhci_tegra_soc_data* soc_data; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int NVQUIRK_ENABLE_BLOCK_GAP_DET ; 
 scalar_t__ SDHCI_BLOCK_GAP_CONTROL ; 
 int SDHCI_INT_CARD_INT ; 
 int SDHCI_INT_CRC ; 
 int SDHCI_INT_ENABLE ; 
 int SDHCI_INT_TIMEOUT ; 
 int SDHCI_SIGNAL_ENABLE ; 
 int readb (scalar_t__) ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tegra_sdhci_writel(struct sdhci_host *host, u32 val, int reg)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	const struct sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;

	/* Seems like we're getting spurious timeout and crc errors, so
	 * disable signalling of them. In case of real errors software
	 * timers should take care of eventually detecting them.
	 */
	if (unlikely(reg == SDHCI_SIGNAL_ENABLE))
		val &= ~(SDHCI_INT_TIMEOUT|SDHCI_INT_CRC);

	writel(val, host->ioaddr + reg);

	if (unlikely((soc_data->nvquirks & NVQUIRK_ENABLE_BLOCK_GAP_DET) &&
			(reg == SDHCI_INT_ENABLE))) {
		/* Erratum: Must enable block gap interrupt detection */
		u8 gap_ctrl = readb(host->ioaddr + SDHCI_BLOCK_GAP_CONTROL);
		if (val & SDHCI_INT_CARD_INT)
			gap_ctrl |= 0x8;
		else
			gap_ctrl &= ~0x8;
		writeb(gap_ctrl, host->ioaddr + SDHCI_BLOCK_GAP_CONTROL);
	}
}