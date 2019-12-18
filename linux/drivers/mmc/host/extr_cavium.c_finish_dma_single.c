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
struct mmc_data {int bytes_xfered; int blocks; int blksz; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; scalar_t__ error; } ;
struct cvm_mmc_host {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_dir (struct mmc_data*) ; 

__attribute__((used)) static int finish_dma_single(struct cvm_mmc_host *host, struct mmc_data *data)
{
	data->bytes_xfered = data->blocks * data->blksz;
	data->error = 0;
	dma_unmap_sg(host->dev, data->sg, data->sg_len, get_dma_dir(data));
	return 1;
}