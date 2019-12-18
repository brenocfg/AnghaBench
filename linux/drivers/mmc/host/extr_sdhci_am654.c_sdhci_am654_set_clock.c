#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {TYPE_2__* mmc; } ;
struct sdhci_am654_data {int dll_on; int otap_del_sel; int flags; int strb_sel; int trm_icp; int drv_strength; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {scalar_t__ timing; } ;
struct TYPE_4__ {TYPE_1__ ios; } ;

/* Variables and functions */
 unsigned int CLOCK_TOO_SLOW_HZ ; 
 int DLLRDY_MASK ; 
 int DLL_TRIM_ICP_MASK ; 
 int DLL_TRIM_ICP_SHIFT ; 
 int DR_TY_MASK ; 
 int DR_TY_SHIFT ; 
 int ENDLL_MASK ; 
 int ENDLL_SHIFT ; 
 int FREQSEL_2_BIT ; 
 int FREQSEL_MASK ; 
 int FREQSEL_SHIFT ; 
 scalar_t__ MMC_TIMING_MMC_HS400 ; 
 int OTAPDLYENA_MASK ; 
 int OTAPDLYENA_SHIFT ; 
 int OTAPDLYSEL_MASK ; 
 int OTAPDLYSEL_SHIFT ; 
 int /*<<< orphan*/  PHY_CTRL1 ; 
 int /*<<< orphan*/  PHY_CTRL4 ; 
 int /*<<< orphan*/  PHY_CTRL5 ; 
 int /*<<< orphan*/  PHY_STAT1 ; 
 int SEL100_MASK ; 
 int SEL100_SHIFT ; 
 int SEL50_MASK ; 
 int SEL50_SHIFT ; 
 int STRBSEL_4BIT_MASK ; 
 int STRBSEL_4_BIT ; 
 int STRBSEL_8BIT_MASK ; 
 int STRBSEL_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_2__*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct sdhci_am654_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_set_clock (struct sdhci_host*,unsigned int) ; 

__attribute__((used)) static void sdhci_am654_set_clock(struct sdhci_host *host, unsigned int clock)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_am654_data *sdhci_am654 = sdhci_pltfm_priv(pltfm_host);
	int sel50, sel100, freqsel;
	u32 mask, val;
	int ret;

	if (sdhci_am654->dll_on) {
		regmap_update_bits(sdhci_am654->base, PHY_CTRL1, ENDLL_MASK, 0);

		sdhci_am654->dll_on = false;
	}

	sdhci_set_clock(host, clock);

	if (clock > CLOCK_TOO_SLOW_HZ) {
		/* Setup DLL Output TAP delay */
		mask = OTAPDLYENA_MASK | OTAPDLYSEL_MASK;
		val = (1 << OTAPDLYENA_SHIFT) |
		      (sdhci_am654->otap_del_sel << OTAPDLYSEL_SHIFT);
		regmap_update_bits(sdhci_am654->base, PHY_CTRL4, mask, val);
		/* Write to STRBSEL for HS400 speed mode */
		if (host->mmc->ios.timing == MMC_TIMING_MMC_HS400) {
			if (sdhci_am654->flags & STRBSEL_4_BIT)
				mask = STRBSEL_4BIT_MASK;
			else
				mask = STRBSEL_8BIT_MASK;

			regmap_update_bits(sdhci_am654->base, PHY_CTRL4, mask,
					   sdhci_am654->strb_sel <<
					   STRBSEL_SHIFT);
		}

		if (sdhci_am654->flags & FREQSEL_2_BIT) {
			switch (clock) {
			case 200000000:
				sel50 = 0;
				sel100 = 0;
				break;
			case 100000000:
				sel50 = 0;
				sel100 = 1;
				break;
			default:
				sel50 = 1;
				sel100 = 0;
			}

			/* Configure PHY DLL frequency */
			mask = SEL50_MASK | SEL100_MASK;
			val = (sel50 << SEL50_SHIFT) | (sel100 << SEL100_SHIFT);
			regmap_update_bits(sdhci_am654->base, PHY_CTRL5, mask,
					   val);
		} else {
			switch (clock) {
			case 200000000:
				freqsel = 0x0;
				break;
			default:
				freqsel = 0x4;
			}

			regmap_update_bits(sdhci_am654->base, PHY_CTRL5,
					   FREQSEL_MASK,
					   freqsel << FREQSEL_SHIFT);
		}

		/* Configure DLL TRIM */
		mask = DLL_TRIM_ICP_MASK;
		val = sdhci_am654->trm_icp << DLL_TRIM_ICP_SHIFT;

		/* Configure DLL driver strength */
		mask |= DR_TY_MASK;
		val |= sdhci_am654->drv_strength << DR_TY_SHIFT;
		regmap_update_bits(sdhci_am654->base, PHY_CTRL1, mask, val);
		/* Enable DLL */
		regmap_update_bits(sdhci_am654->base, PHY_CTRL1, ENDLL_MASK,
				   0x1 << ENDLL_SHIFT);
		/*
		 * Poll for DLL ready. Use a one second timeout.
		 * Works in all experiments done so far
		 */
		ret = regmap_read_poll_timeout(sdhci_am654->base, PHY_STAT1,
					       val, val & DLLRDY_MASK, 1000,
					       1000000);
		if (ret) {
			dev_err(mmc_dev(host->mmc), "DLL failed to relock\n");
			return;
		}

		sdhci_am654->dll_on = true;
	}
}