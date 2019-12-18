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
struct mmc_data {int host_cookie; int sg_count; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct jz4740_mmc_host {int /*<<< orphan*/  mmc; } ;
struct dma_chan {TYPE_1__* device; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int COOKIE_PREMAPPED ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dma_chan* jz4740_mmc_get_dma_chan (struct jz4740_mmc_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mmc_get_dma_dir (struct mmc_data*) ; 

__attribute__((used)) static int jz4740_mmc_prepare_dma_data(struct jz4740_mmc_host *host,
				       struct mmc_data *data,
				       int cookie)
{
	struct dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);
	enum dma_data_direction dir = mmc_get_dma_dir(data);
	int sg_count;

	if (data->host_cookie == COOKIE_PREMAPPED)
		return data->sg_count;

	sg_count = dma_map_sg(chan->device->dev,
			data->sg,
			data->sg_len,
			dir);

	if (sg_count <= 0) {
		dev_err(mmc_dev(host->mmc),
			"Failed to map scatterlist for DMA operation\n");
		return -EINVAL;
	}

	data->sg_count = sg_count;
	data->host_cookie = cookie;

	return data->sg_count;
}