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
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_msm_offset {int /*<<< orphan*/  core_pwrctl_ctl; int /*<<< orphan*/  core_pwrctl_mask; int /*<<< orphan*/  core_pwrctl_status; } ;
struct sdhci_msm_host {struct sdhci_msm_offset* offset; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_host_readl (struct sdhci_msm_host*,struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sdhci_msm_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static void sdhci_msm_dump_pwr_ctrl_regs(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	const struct sdhci_msm_offset *msm_offset =
					msm_host->offset;

	pr_err("%s: PWRCTL_STATUS: 0x%08x | PWRCTL_MASK: 0x%08x | PWRCTL_CTL: 0x%08x\n",
		mmc_hostname(host->mmc),
		msm_host_readl(msm_host, host, msm_offset->core_pwrctl_status),
		msm_host_readl(msm_host, host, msm_offset->core_pwrctl_mask),
		msm_host_readl(msm_host, host, msm_offset->core_pwrctl_ctl));
}