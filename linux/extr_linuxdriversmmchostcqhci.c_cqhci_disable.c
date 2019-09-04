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
struct mmc_host {struct cqhci_host* cqe_private; } ;
struct cqhci_host {int enabled; int /*<<< orphan*/ * desc_base; int /*<<< orphan*/ * trans_desc_base; int /*<<< orphan*/  desc_dma_base; int /*<<< orphan*/  desc_size; int /*<<< orphan*/  trans_desc_dma_base; int /*<<< orphan*/  data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cqhci_disable (struct cqhci_host*) ; 
 int /*<<< orphan*/  cqhci_off (struct mmc_host*) ; 
 int /*<<< orphan*/  dmam_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 

__attribute__((used)) static void cqhci_disable(struct mmc_host *mmc)
{
	struct cqhci_host *cq_host = mmc->cqe_private;

	if (!cq_host->enabled)
		return;

	cqhci_off(mmc);

	__cqhci_disable(cq_host);

	dmam_free_coherent(mmc_dev(mmc), cq_host->data_size,
			   cq_host->trans_desc_base,
			   cq_host->trans_desc_dma_base);

	dmam_free_coherent(mmc_dev(mmc), cq_host->desc_size,
			   cq_host->desc_base,
			   cq_host->desc_dma_base);

	cq_host->trans_desc_base = NULL;
	cq_host->desc_base = NULL;

	cq_host->enabled = false;
}