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
struct sdhci_msm_offset {scalar_t__ core_dll_config; } ;
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_CDR_EN ; 
 int /*<<< orphan*/  CORE_CDR_EXT_EN ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct sdhci_msm_offset* sdhci_priv_msm_offset (struct sdhci_host*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sdhci_msm_set_cdr(struct sdhci_host *host, bool enable)
{
	const struct sdhci_msm_offset *msm_offset = sdhci_priv_msm_offset(host);
	u32 config, oldconfig = readl_relaxed(host->ioaddr +
					      msm_offset->core_dll_config);

	config = oldconfig;
	if (enable) {
		config |= CORE_CDR_EN;
		config &= ~CORE_CDR_EXT_EN;
	} else {
		config &= ~CORE_CDR_EN;
		config |= CORE_CDR_EXT_EN;
	}

	if (config != oldconfig) {
		writel_relaxed(config, host->ioaddr +
			       msm_offset->core_dll_config);
	}
}