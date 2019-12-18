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
struct mmc_request {struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {scalar_t__ host_cookie; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct dw_mci_slot {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  use_dma; } ;

/* Variables and functions */
 scalar_t__ COOKIE_UNMAPPED ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 
 struct dw_mci_slot* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void dw_mci_post_req(struct mmc_host *mmc,
			    struct mmc_request *mrq,
			    int err)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct mmc_data *data = mrq->data;

	if (!slot->host->use_dma || !data)
		return;

	if (data->host_cookie != COOKIE_UNMAPPED)
		dma_unmap_sg(slot->host->dev,
			     data->sg,
			     data->sg_len,
			     mmc_get_dma_dir(data));
	data->host_cookie = COOKIE_UNMAPPED;
}