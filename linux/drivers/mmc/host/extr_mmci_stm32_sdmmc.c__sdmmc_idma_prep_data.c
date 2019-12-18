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
struct mmci_host {int /*<<< orphan*/  mmc; } ;
struct mmc_data {int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 

__attribute__((used)) static int _sdmmc_idma_prep_data(struct mmci_host *host,
				 struct mmc_data *data)
{
	int n_elem;

	n_elem = dma_map_sg(mmc_dev(host->mmc),
			    data->sg,
			    data->sg_len,
			    mmc_get_dma_dir(data));

	if (!n_elem) {
		dev_err(mmc_dev(host->mmc), "dma_map_sg failed\n");
		return -EINVAL;
	}

	return 0;
}