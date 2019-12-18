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
typedef  int u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {unsigned int clock; int flags; int /*<<< orphan*/  tuning_err; } ;
struct sdhci_esdhc {int peripheral_clock; int div_ratio; scalar_t__ quirk_fixup_tuning; scalar_t__ quirk_limited_clk_division; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int ESDHC_FLW_CTL_BG ; 
 int /*<<< orphan*/  ESDHC_SDTIMNGCTL ; 
 int /*<<< orphan*/  ESDHC_TBCTL ; 
 int /*<<< orphan*/  ESDHC_TBPTR ; 
 int SDHCI_HS400_TUNING ; 
 int /*<<< orphan*/  esdhc_of_set_clock (struct sdhci_host*,unsigned int) ; 
 int /*<<< orphan*/  esdhc_tuning_block_enable (struct sdhci_host*,int) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int sdhci_execute_tuning (struct mmc_host*,int) ; 
 struct sdhci_esdhc* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esdhc_execute_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct sdhci_host *host = mmc_priv(mmc);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	bool hs400_tuning;
	unsigned int clk;
	u32 val;
	int ret;

	/* For tuning mode, the sd clock divisor value
	 * must be larger than 3 according to reference manual.
	 */
	clk = esdhc->peripheral_clock / 3;
	if (host->clock > clk)
		esdhc_of_set_clock(host, clk);

	if (esdhc->quirk_limited_clk_division &&
	    host->flags & SDHCI_HS400_TUNING)
		esdhc_of_set_clock(host, host->clock);

	esdhc_tuning_block_enable(host, true);

	hs400_tuning = host->flags & SDHCI_HS400_TUNING;
	ret = sdhci_execute_tuning(mmc, opcode);

	if (hs400_tuning) {
		val = sdhci_readl(host, ESDHC_SDTIMNGCTL);
		val |= ESDHC_FLW_CTL_BG;
		sdhci_writel(host, val, ESDHC_SDTIMNGCTL);
	}

	if (host->tuning_err == -EAGAIN && esdhc->quirk_fixup_tuning) {

		/* program TBPTR[TB_WNDW_END_PTR] = 3*DIV_RATIO and
		 * program TBPTR[TB_WNDW_START_PTR] = 5*DIV_RATIO
		 */
		val = sdhci_readl(host, ESDHC_TBPTR);
		val = (val & ~((0x7f << 8) | 0x7f)) |
		(3 * esdhc->div_ratio) | ((5 * esdhc->div_ratio) << 8);
		sdhci_writel(host, val, ESDHC_TBPTR);

		/* program the software tuning mode by setting
		 * TBCTL[TB_MODE]=2'h3
		 */
		val = sdhci_readl(host, ESDHC_TBCTL);
		val |= 0x3;
		sdhci_writel(host, val, ESDHC_TBCTL);
		sdhci_execute_tuning(mmc, opcode);
	}
	return ret;
}