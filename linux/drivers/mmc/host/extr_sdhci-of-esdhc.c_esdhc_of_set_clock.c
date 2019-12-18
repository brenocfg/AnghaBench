#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int max_clk; int flags; TYPE_3__* mmc; } ;
struct sdhci_esdhc {scalar_t__ vendor_ver; int div_ratio; scalar_t__ quirk_limited_clk_division; TYPE_1__* clk_fixup; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_6__ {size_t timing; } ;
struct TYPE_7__ {int actual_clock; TYPE_2__ ios; scalar_t__ card; } ;
struct TYPE_5__ {long sd_dflt_max_clk; long* max_clk; } ;

/* Variables and functions */
 int ESDHC_CLOCK_HCKEN ; 
 int ESDHC_CLOCK_IPGEN ; 
 int ESDHC_CLOCK_MASK ; 
 int ESDHC_CLOCK_PEREN ; 
 int ESDHC_CLOCK_SDCLKEN ; 
 int ESDHC_CLOCK_STABLE ; 
 int ESDHC_CMD_CLK_CTL ; 
 int ESDHC_DIVIDER_SHIFT ; 
 int /*<<< orphan*/  ESDHC_DLLCFG0 ; 
 int ESDHC_DLL_ENABLE ; 
 int ESDHC_DLL_FREQ_SEL ; 
 int /*<<< orphan*/  ESDHC_DMA_SYSCTL ; 
 int ESDHC_FLUSH_ASYNC_FIFO ; 
 int ESDHC_HS400_MODE ; 
 int ESDHC_HS400_WNDW_ADJUST ; 
 int ESDHC_PREDIV_SHIFT ; 
 int /*<<< orphan*/  ESDHC_PRSSTAT ; 
 int /*<<< orphan*/  ESDHC_SDCLKCTL ; 
 int /*<<< orphan*/  ESDHC_SYSTEM_CONTROL ; 
 int /*<<< orphan*/  ESDHC_TBCTL ; 
 unsigned int MMC_HS200_MAX_DTR ; 
 size_t MMC_TIMING_LEGACY ; 
 size_t MMC_TIMING_MMC_HS400 ; 
 int SDHCI_HS400_TUNING ; 
 scalar_t__ VENDOR_V_23 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  esdhc_clock_enable (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,int) ; 
 int ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ mmc_card_sd (scalar_t__) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 struct sdhci_esdhc* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void esdhc_of_set_clock(struct sdhci_host *host, unsigned int clock)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	int pre_div = 1;
	int div = 1;
	int division;
	ktime_t timeout;
	long fixup = 0;
	u32 temp;

	host->mmc->actual_clock = 0;

	if (clock == 0) {
		esdhc_clock_enable(host, false);
		return;
	}

	/* Workaround to start pre_div at 2 for VNN < VENDOR_V_23 */
	if (esdhc->vendor_ver < VENDOR_V_23)
		pre_div = 2;

	if (host->mmc->card && mmc_card_sd(host->mmc->card) &&
		esdhc->clk_fixup && host->mmc->ios.timing == MMC_TIMING_LEGACY)
		fixup = esdhc->clk_fixup->sd_dflt_max_clk;
	else if (esdhc->clk_fixup)
		fixup = esdhc->clk_fixup->max_clk[host->mmc->ios.timing];

	if (fixup && clock > fixup)
		clock = fixup;

	temp = sdhci_readl(host, ESDHC_SYSTEM_CONTROL);
	temp &= ~(ESDHC_CLOCK_SDCLKEN | ESDHC_CLOCK_IPGEN | ESDHC_CLOCK_HCKEN |
		  ESDHC_CLOCK_PEREN | ESDHC_CLOCK_MASK);
	sdhci_writel(host, temp, ESDHC_SYSTEM_CONTROL);

	while (host->max_clk / pre_div / 16 > clock && pre_div < 256)
		pre_div *= 2;

	while (host->max_clk / pre_div / div > clock && div < 16)
		div++;

	if (esdhc->quirk_limited_clk_division &&
	    clock == MMC_HS200_MAX_DTR &&
	    (host->mmc->ios.timing == MMC_TIMING_MMC_HS400 ||
	     host->flags & SDHCI_HS400_TUNING)) {
		division = pre_div * div;
		if (division <= 4) {
			pre_div = 4;
			div = 1;
		} else if (division <= 8) {
			pre_div = 4;
			div = 2;
		} else if (division <= 12) {
			pre_div = 4;
			div = 3;
		} else {
			pr_warn("%s: using unsupported clock division.\n",
				mmc_hostname(host->mmc));
		}
	}

	dev_dbg(mmc_dev(host->mmc), "desired SD clock: %d, actual: %d\n",
		clock, host->max_clk / pre_div / div);
	host->mmc->actual_clock = host->max_clk / pre_div / div;
	esdhc->div_ratio = pre_div * div;
	pre_div >>= 1;
	div--;

	temp = sdhci_readl(host, ESDHC_SYSTEM_CONTROL);
	temp |= (ESDHC_CLOCK_IPGEN | ESDHC_CLOCK_HCKEN | ESDHC_CLOCK_PEREN
		| (div << ESDHC_DIVIDER_SHIFT)
		| (pre_div << ESDHC_PREDIV_SHIFT));
	sdhci_writel(host, temp, ESDHC_SYSTEM_CONTROL);

	if (host->mmc->ios.timing == MMC_TIMING_MMC_HS400 &&
	    clock == MMC_HS200_MAX_DTR) {
		temp = sdhci_readl(host, ESDHC_TBCTL);
		sdhci_writel(host, temp | ESDHC_HS400_MODE, ESDHC_TBCTL);
		temp = sdhci_readl(host, ESDHC_SDCLKCTL);
		sdhci_writel(host, temp | ESDHC_CMD_CLK_CTL, ESDHC_SDCLKCTL);
		esdhc_clock_enable(host, true);

		temp = sdhci_readl(host, ESDHC_DLLCFG0);
		temp |= ESDHC_DLL_ENABLE;
		if (host->mmc->actual_clock == MMC_HS200_MAX_DTR)
			temp |= ESDHC_DLL_FREQ_SEL;
		sdhci_writel(host, temp, ESDHC_DLLCFG0);
		temp = sdhci_readl(host, ESDHC_TBCTL);
		sdhci_writel(host, temp | ESDHC_HS400_WNDW_ADJUST, ESDHC_TBCTL);

		esdhc_clock_enable(host, false);
		temp = sdhci_readl(host, ESDHC_DMA_SYSCTL);
		temp |= ESDHC_FLUSH_ASYNC_FIFO;
		sdhci_writel(host, temp, ESDHC_DMA_SYSCTL);
	}

	/* Wait max 20 ms */
	timeout = ktime_add_ms(ktime_get(), 20);
	while (1) {
		bool timedout = ktime_after(ktime_get(), timeout);

		if (sdhci_readl(host, ESDHC_PRSSTAT) & ESDHC_CLOCK_STABLE)
			break;
		if (timedout) {
			pr_err("%s: Internal clock never stabilised.\n",
				mmc_hostname(host->mmc));
			return;
		}
		udelay(10);
	}

	temp = sdhci_readl(host, ESDHC_SYSTEM_CONTROL);
	temp |= ESDHC_CLOCK_SDCLKEN;
	sdhci_writel(host, temp, ESDHC_SYSTEM_CONTROL);
}