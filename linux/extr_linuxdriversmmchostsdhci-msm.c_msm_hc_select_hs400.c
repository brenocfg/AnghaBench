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
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_msm_offset {scalar_t__ core_dll_status; scalar_t__ core_vendor_spec; } ;
struct sdhci_msm_host {int /*<<< orphan*/  use_cdclp533; int /*<<< orphan*/  clk_rate; int /*<<< orphan*/  calibration_done; scalar_t__ tuning_done; struct sdhci_msm_offset* offset; } ;
struct sdhci_host {TYPE_1__* mmc; scalar_t__ ioaddr; } ;
struct mmc_ios {scalar_t__ enhanced_strobe; } ;
struct TYPE_2__ {struct mmc_ios ios; } ;

/* Variables and functions */
 int CORE_DDR_DLL_LOCK ; 
 int CORE_DLL_LOCK ; 
 int CORE_HC_MCLK_SEL_HS400 ; 
 int CORE_HC_MCLK_SEL_MASK ; 
 int CORE_HC_SELECT_IN_EN ; 
 int CORE_HC_SELECT_IN_HS400 ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int readl_relaxed (scalar_t__) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int,int) ; 
 struct sdhci_msm_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void msm_hc_select_hs400(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	struct mmc_ios ios = host->mmc->ios;
	u32 config, dll_lock;
	int rc;
	const struct sdhci_msm_offset *msm_offset =
					msm_host->offset;

	/* Select the divided clock (free running MCLK/2) */
	config = readl_relaxed(host->ioaddr + msm_offset->core_vendor_spec);
	config &= ~CORE_HC_MCLK_SEL_MASK;
	config |= CORE_HC_MCLK_SEL_HS400;

	writel_relaxed(config, host->ioaddr + msm_offset->core_vendor_spec);
	/*
	 * Select HS400 mode using the HC_SELECT_IN from VENDOR SPEC
	 * register
	 */
	if ((msm_host->tuning_done || ios.enhanced_strobe) &&
	    !msm_host->calibration_done) {
		config = readl_relaxed(host->ioaddr +
				msm_offset->core_vendor_spec);
		config |= CORE_HC_SELECT_IN_HS400;
		config |= CORE_HC_SELECT_IN_EN;
		writel_relaxed(config, host->ioaddr +
				msm_offset->core_vendor_spec);
	}
	if (!msm_host->clk_rate && !msm_host->use_cdclp533) {
		/*
		 * Poll on DLL_LOCK or DDR_DLL_LOCK bits in
		 * core_dll_status to be set. This should get set
		 * within 15 us at 200 MHz.
		 */
		rc = readl_relaxed_poll_timeout(host->ioaddr +
						msm_offset->core_dll_status,
						dll_lock,
						(dll_lock &
						(CORE_DLL_LOCK |
						CORE_DDR_DLL_LOCK)), 10,
						1000);
		if (rc == -ETIMEDOUT)
			pr_err("%s: Unable to get DLL_LOCK/DDR_DLL_LOCK, dll_status: 0x%08x\n",
			       mmc_hostname(host->mmc), dll_lock);
	}
	/*
	 * Make sure above writes impacting free running MCLK are completed
	 * before changing the clk_rate at GCC.
	 */
	wmb();
}