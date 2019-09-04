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
struct sdhci_host {int tuning_delay; int /*<<< orphan*/  sdma_boundary; int /*<<< orphan*/  cqe_err_ier; int /*<<< orphan*/  cqe_ier; int /*<<< orphan*/  flags; int /*<<< orphan*/  mmc_host_ops; struct mmc_host* mmc; } ;
struct mmc_host {int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sdhci_host* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDHCI_CQE_INT_ERR_MASK ; 
 int /*<<< orphan*/  SDHCI_CQE_INT_MASK ; 
 int /*<<< orphan*/  SDHCI_DEFAULT_BOUNDARY_ARG ; 
 int /*<<< orphan*/  SDHCI_SIGNALING_330 ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct mmc_host* mmc_alloc_host (int,struct device*) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sdhci_ops ; 

struct sdhci_host *sdhci_alloc_host(struct device *dev,
	size_t priv_size)
{
	struct mmc_host *mmc;
	struct sdhci_host *host;

	WARN_ON(dev == NULL);

	mmc = mmc_alloc_host(sizeof(struct sdhci_host) + priv_size, dev);
	if (!mmc)
		return ERR_PTR(-ENOMEM);

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->mmc_host_ops = sdhci_ops;
	mmc->ops = &host->mmc_host_ops;

	host->flags = SDHCI_SIGNALING_330;

	host->cqe_ier     = SDHCI_CQE_INT_MASK;
	host->cqe_err_ier = SDHCI_CQE_INT_ERR_MASK;

	host->tuning_delay = -1;

	host->sdma_boundary = SDHCI_DEFAULT_BOUNDARY_ARG;

	return host;
}