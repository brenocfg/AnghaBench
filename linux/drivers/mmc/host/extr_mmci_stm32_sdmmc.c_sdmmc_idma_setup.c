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
struct sdmmc_priv {int /*<<< orphan*/  sg_cpu; int /*<<< orphan*/  sg_dma; } ;
struct sdmmc_lli_desc {int dummy; } ;
struct mmci_host {TYPE_2__* mmc; TYPE_1__* variant; struct sdmmc_priv* dma_priv; } ;
struct TYPE_4__ {int max_segs; int /*<<< orphan*/  max_req_size; int /*<<< orphan*/  max_seg_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  stm32_idmabsize_mask; scalar_t__ dma_lli; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SDMMC_LLI_BUF_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sdmmc_priv* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_2__*) ; 

__attribute__((used)) static int sdmmc_idma_setup(struct mmci_host *host)
{
	struct sdmmc_priv *idma;

	idma = devm_kzalloc(mmc_dev(host->mmc), sizeof(*idma), GFP_KERNEL);
	if (!idma)
		return -ENOMEM;

	host->dma_priv = idma;

	if (host->variant->dma_lli) {
		idma->sg_cpu = dmam_alloc_coherent(mmc_dev(host->mmc),
						   SDMMC_LLI_BUF_LEN,
						   &idma->sg_dma, GFP_KERNEL);
		if (!idma->sg_cpu) {
			dev_err(mmc_dev(host->mmc),
				"Failed to alloc IDMA descriptor\n");
			return -ENOMEM;
		}
		host->mmc->max_segs = SDMMC_LLI_BUF_LEN /
			sizeof(struct sdmmc_lli_desc);
		host->mmc->max_seg_size = host->variant->stm32_idmabsize_mask;
	} else {
		host->mmc->max_segs = 1;
		host->mmc->max_seg_size = host->mmc->max_req_size;
	}

	return 0;
}