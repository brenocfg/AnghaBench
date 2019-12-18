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
struct sh_mmcif_host {int blocksize; int /*<<< orphan*/  pio_ptr; scalar_t__ sg_blkidx; scalar_t__ sg_idx; int /*<<< orphan*/  wait_for; int /*<<< orphan*/  addr; } ;
struct mmc_request {struct mmc_data* data; } ;
struct mmc_data {TYPE_1__* sg; int /*<<< orphan*/  sg_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int BLOCK_SIZE_MASK ; 
 int /*<<< orphan*/  MASK_MBUFREN ; 
 int /*<<< orphan*/  MMCIF_CE_BLOCK_SET ; 
 int /*<<< orphan*/  MMCIF_CE_INT_MASK ; 
 int /*<<< orphan*/  MMCIF_WAIT_FOR_MREAD ; 
 int /*<<< orphan*/  sg_virt (TYPE_1__*) ; 
 int /*<<< orphan*/  sh_mmcif_bitset (struct sh_mmcif_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sh_mmcif_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mmcif_multi_read(struct sh_mmcif_host *host,
				struct mmc_request *mrq)
{
	struct mmc_data *data = mrq->data;

	if (!data->sg_len || !data->sg->length)
		return;

	host->blocksize = sh_mmcif_readl(host->addr, MMCIF_CE_BLOCK_SET) &
		BLOCK_SIZE_MASK;

	host->wait_for = MMCIF_WAIT_FOR_MREAD;
	host->sg_idx = 0;
	host->sg_blkidx = 0;
	host->pio_ptr = sg_virt(data->sg);

	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFREN);
}