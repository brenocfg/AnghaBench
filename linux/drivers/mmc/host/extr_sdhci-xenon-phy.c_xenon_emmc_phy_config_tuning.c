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
struct xenon_priv {struct xenon_emmc_phy_params* phy_params; } ;
struct xenon_emmc_phy_params {int tun_step_divider; int nr_tun_times; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {scalar_t__ clock; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MMC_HIGH_52_MAX_DTR ; 
 int /*<<< orphan*/  XENON_SLOT_DLL_CUR_DLY_VAL ; 
 int /*<<< orphan*/  XENON_SLOT_OP_STATUS_CTRL ; 
 int XENON_TUNING_STEP_MASK ; 
 int XENON_TUNING_STEP_SHIFT ; 
 int XENON_TUN_CONSECUTIVE_TIMES_MASK ; 
 int XENON_TUN_CONSECUTIVE_TIMES_SHIFT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct xenon_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int xenon_emmc_phy_enable_dll (struct sdhci_host*) ; 

__attribute__((used)) static int xenon_emmc_phy_config_tuning(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	struct xenon_emmc_phy_params *params = priv->phy_params;
	u32 reg, tuning_step;
	int ret;

	if (host->clock <= MMC_HIGH_52_MAX_DTR)
		return -EINVAL;

	ret = xenon_emmc_phy_enable_dll(host);
	if (ret)
		return ret;

	/* Achieve TUNING_STEP with HW DLL help */
	reg = sdhci_readl(host, XENON_SLOT_DLL_CUR_DLY_VAL);
	tuning_step = reg / params->tun_step_divider;
	if (unlikely(tuning_step > XENON_TUNING_STEP_MASK)) {
		dev_warn(mmc_dev(host->mmc),
			 "HS200 TUNING_STEP %d is larger than MAX value\n",
			 tuning_step);
		tuning_step = XENON_TUNING_STEP_MASK;
	}

	/* Set TUNING_STEP for later tuning */
	reg = sdhci_readl(host, XENON_SLOT_OP_STATUS_CTRL);
	reg &= ~(XENON_TUN_CONSECUTIVE_TIMES_MASK <<
		 XENON_TUN_CONSECUTIVE_TIMES_SHIFT);
	reg |= (params->nr_tun_times << XENON_TUN_CONSECUTIVE_TIMES_SHIFT);
	reg &= ~(XENON_TUNING_STEP_MASK << XENON_TUNING_STEP_SHIFT);
	reg |= (tuning_step << XENON_TUNING_STEP_SHIFT);
	sdhci_writel(host, reg, XENON_SLOT_OP_STATUS_CTRL);

	return 0;
}