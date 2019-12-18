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
struct mmc_request {struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {int /*<<< orphan*/  sg_count; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; int /*<<< orphan*/  host_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EMMC_PRE_REQ_DONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_mmc_desc_chain_mode (struct mmc_data*) ; 
 int /*<<< orphan*/  meson_mmc_get_transfer_mode (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 

__attribute__((used)) static void meson_mmc_pre_req(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct mmc_data *data = mrq->data;

	if (!data)
		return;

	meson_mmc_get_transfer_mode(mmc, mrq);
	data->host_cookie |= SD_EMMC_PRE_REQ_DONE;

	if (!meson_mmc_desc_chain_mode(data))
		return;

	data->sg_count = dma_map_sg(mmc_dev(mmc), data->sg, data->sg_len,
                                   mmc_get_dma_dir(data));
	if (!data->sg_count)
		dev_err(mmc_dev(mmc), "dma_map_sg failed");
}