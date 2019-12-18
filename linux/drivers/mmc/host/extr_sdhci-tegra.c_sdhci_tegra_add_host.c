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
struct sdhci_tegra {int /*<<< orphan*/  enable_hwcq; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int flags; TYPE_1__* mmc; scalar_t__ ioaddr; } ;
struct cqhci_host {int /*<<< orphan*/  caps; int /*<<< orphan*/ * ops; scalar_t__ mmio; } ;
struct TYPE_2__ {int caps2; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_TASK_DESC_SZ_128 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MMC_CAP2_CQE ; 
 int MMC_CAP2_CQE_DCMD ; 
 scalar_t__ SDHCI_TEGRA_CQE_BASE_ADDR ; 
 int SDHCI_USE_64_BIT_DMA ; 
 int __sdhci_add_host (struct sdhci_host*) ; 
 int cqhci_init (struct cqhci_host*,TYPE_1__*,int) ; 
 struct cqhci_host* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_cleanup_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_enable_v4_mode (struct sdhci_host*) ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_setup_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_tegra_cqhci_ops ; 

__attribute__((used)) static int sdhci_tegra_add_host(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	struct cqhci_host *cq_host;
	bool dma64;
	int ret;

	if (!tegra_host->enable_hwcq)
		return sdhci_add_host(host);

	sdhci_enable_v4_mode(host);

	ret = sdhci_setup_host(host);
	if (ret)
		return ret;

	host->mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;

	cq_host = devm_kzalloc(host->mmc->parent,
				sizeof(*cq_host), GFP_KERNEL);
	if (!cq_host) {
		ret = -ENOMEM;
		goto cleanup;
	}

	cq_host->mmio = host->ioaddr + SDHCI_TEGRA_CQE_BASE_ADDR;
	cq_host->ops = &sdhci_tegra_cqhci_ops;

	dma64 = host->flags & SDHCI_USE_64_BIT_DMA;
	if (dma64)
		cq_host->caps |= CQHCI_TASK_DESC_SZ_128;

	ret = cqhci_init(cq_host, host->mmc, dma64);
	if (ret)
		goto cleanup;

	ret = __sdhci_add_host(host);
	if (ret)
		goto cleanup;

	return 0;

cleanup:
	sdhci_cleanup_host(host);
	return ret;
}