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
struct scatterlist {int offset; int length; } ;
struct mmc_request {struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {int /*<<< orphan*/  sg_len; struct scatterlist* sg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 

__attribute__((used)) static int meson_mx_mmc_map_dma(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct mmc_data *data = mrq->data;
	int dma_len;
	struct scatterlist *sg;

	if (!data)
		return 0;

	sg = data->sg;
	if (sg->offset & 3 || sg->length & 3) {
		dev_err(mmc_dev(mmc),
			"unaligned scatterlist: offset %x length %d\n",
			sg->offset, sg->length);
		return -EINVAL;
	}

	dma_len = dma_map_sg(mmc_dev(mmc), data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
	if (dma_len <= 0) {
		dev_err(mmc_dev(mmc), "dma_map_sg failed\n");
		return -ENOMEM;
	}

	return 0;
}