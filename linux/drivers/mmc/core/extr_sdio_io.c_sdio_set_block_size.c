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
struct sdio_func {unsigned int max_blksize; unsigned int cur_blksize; int /*<<< orphan*/  num; TYPE_2__* card; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {unsigned int max_blk_size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SDIO_FBR_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__ SDIO_FBR_BLKSIZE ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int mmc_io_rw_direct (TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ *) ; 

int sdio_set_block_size(struct sdio_func *func, unsigned blksz)
{
	int ret;

	if (blksz > func->card->host->max_blk_size)
		return -EINVAL;

	if (blksz == 0) {
		blksz = min(func->max_blksize, func->card->host->max_blk_size);
		blksz = min(blksz, 512u);
	}

	ret = mmc_io_rw_direct(func->card, 1, 0,
		SDIO_FBR_BASE(func->num) + SDIO_FBR_BLKSIZE,
		blksz & 0xff, NULL);
	if (ret)
		return ret;
	ret = mmc_io_rw_direct(func->card, 1, 0,
		SDIO_FBR_BASE(func->num) + SDIO_FBR_BLKSIZE + 1,
		(blksz >> 8) & 0xff, NULL);
	if (ret)
		return ret;
	func->cur_blksize = blksz;
	return 0;
}