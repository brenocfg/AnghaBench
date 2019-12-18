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
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int /*<<< orphan*/  ier; } ;
struct sdhci_esdhc {scalar_t__ quirk_unreliable_pulse_detection; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESDHC_DLLCFG1 ; 
 int /*<<< orphan*/  ESDHC_DLL_PD_PULSE_STRETCH_SEL ; 
 int /*<<< orphan*/  ESDHC_TBCTL ; 
 int /*<<< orphan*/  ESDHC_TB_EN ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct sdhci_esdhc* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esdhc_reset(struct sdhci_host *host, u8 mask)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	u32 val;

	sdhci_reset(host, mask);

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);

	if (of_find_compatible_node(NULL, NULL, "fsl,p2020-esdhc"))
		mdelay(5);

	if (mask & SDHCI_RESET_ALL) {
		val = sdhci_readl(host, ESDHC_TBCTL);
		val &= ~ESDHC_TB_EN;
		sdhci_writel(host, val, ESDHC_TBCTL);

		if (esdhc->quirk_unreliable_pulse_detection) {
			val = sdhci_readl(host, ESDHC_DLLCFG1);
			val &= ~ESDHC_DLL_PD_PULSE_STRETCH_SEL;
			sdhci_writel(host, val, ESDHC_DLLCFG1);
		}
	}
}