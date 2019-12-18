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
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_omap_host {int flags; struct pinctrl_state** pinctrl_state; struct pinctrl_state* pinctrl; struct device* dev; struct sdhci_host* host; } ;
struct sdhci_host {struct mmc_host* mmc; } ;
struct pinctrl_state {int dummy; } ;
struct mmc_host {int /*<<< orphan*/  caps2; int /*<<< orphan*/  caps; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pinctrl_state*) ; 
 int /*<<< orphan*/  MMC_CAP2_HS200_1_8V_SDR ; 
 int /*<<< orphan*/  MMC_CAP_1_8V_DDR ; 
 int /*<<< orphan*/  MMC_CAP_3_3V_DDR ; 
 int /*<<< orphan*/  MMC_CAP_MMC_HIGHSPEED ; 
 int /*<<< orphan*/  MMC_CAP_SD_HIGHSPEED ; 
 int /*<<< orphan*/  MMC_CAP_UHS_DDR50 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_SDR104 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_SDR12 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_SDR25 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_SDR50 ; 
 size_t MMC_TIMING_LEGACY ; 
 size_t MMC_TIMING_MMC_DDR52 ; 
 size_t MMC_TIMING_MMC_HS ; 
 int MMC_TIMING_MMC_HS200 ; 
 size_t MMC_TIMING_SD_HS ; 
 size_t MMC_TIMING_UHS_DDR50 ; 
 size_t MMC_TIMING_UHS_SDR104 ; 
 size_t MMC_TIMING_UHS_SDR12 ; 
 size_t MMC_TIMING_UHS_SDR25 ; 
 size_t MMC_TIMING_UHS_SDR50 ; 
 int PTR_ERR (struct pinctrl_state*) ; 
 int SDHCI_OMAP_REQUIRE_IODELAY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pinctrl_state** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct pinctrl_state* devm_pinctrl_get (struct device*) ; 
 struct pinctrl_state* pinctrl_lookup_state (struct pinctrl_state*,char*) ; 
 struct pinctrl_state* sdhci_omap_iodelay_pinctrl_state (struct sdhci_omap_host*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdhci_omap_config_iodelay_pinctrl_state(struct sdhci_omap_host
						   *omap_host)
{
	struct device *dev = omap_host->dev;
	struct sdhci_host *host = omap_host->host;
	struct mmc_host *mmc = host->mmc;
	u32 *caps = &mmc->caps;
	u32 *caps2 = &mmc->caps2;
	struct pinctrl_state *state;
	struct pinctrl_state **pinctrl_state;

	if (!(omap_host->flags & SDHCI_OMAP_REQUIRE_IODELAY))
		return 0;

	pinctrl_state = devm_kcalloc(dev,
				     MMC_TIMING_MMC_HS200 + 1,
				     sizeof(*pinctrl_state),
				     GFP_KERNEL);
	if (!pinctrl_state)
		return -ENOMEM;

	omap_host->pinctrl = devm_pinctrl_get(omap_host->dev);
	if (IS_ERR(omap_host->pinctrl)) {
		dev_err(dev, "Cannot get pinctrl\n");
		return PTR_ERR(omap_host->pinctrl);
	}

	state = pinctrl_lookup_state(omap_host->pinctrl, "default");
	if (IS_ERR(state)) {
		dev_err(dev, "no pinctrl state for default mode\n");
		return PTR_ERR(state);
	}
	pinctrl_state[MMC_TIMING_LEGACY] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "sdr104", caps,
						 MMC_CAP_UHS_SDR104);
	if (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_SDR104] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "ddr50", caps,
						 MMC_CAP_UHS_DDR50);
	if (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_DDR50] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "sdr50", caps,
						 MMC_CAP_UHS_SDR50);
	if (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_SDR50] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "sdr25", caps,
						 MMC_CAP_UHS_SDR25);
	if (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_SDR25] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "sdr12", caps,
						 MMC_CAP_UHS_SDR12);
	if (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_SDR12] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "ddr_1_8v", caps,
						 MMC_CAP_1_8V_DDR);
	if (!IS_ERR(state)) {
		pinctrl_state[MMC_TIMING_MMC_DDR52] = state;
	} else {
		state = sdhci_omap_iodelay_pinctrl_state(omap_host, "ddr_3_3v",
							 caps,
							 MMC_CAP_3_3V_DDR);
		if (!IS_ERR(state))
			pinctrl_state[MMC_TIMING_MMC_DDR52] = state;
	}

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "hs", caps,
						 MMC_CAP_SD_HIGHSPEED);
	if (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_SD_HS] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "hs", caps,
						 MMC_CAP_MMC_HIGHSPEED);
	if (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_MMC_HS] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "hs200_1_8v", caps2,
						 MMC_CAP2_HS200_1_8V_SDR);
	if (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_MMC_HS200] = state;

	omap_host->pinctrl_state = pinctrl_state;

	return 0;
}