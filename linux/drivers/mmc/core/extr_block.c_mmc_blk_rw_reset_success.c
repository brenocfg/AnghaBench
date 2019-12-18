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
struct request {int dummy; } ;
struct mmc_queue {int /*<<< orphan*/  blkdata; } ;

/* Variables and functions */
 int MMC_BLK_READ ; 
 int MMC_BLK_WRITE ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  mmc_blk_reset_success (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static inline void mmc_blk_rw_reset_success(struct mmc_queue *mq,
					    struct request *req)
{
	int type = rq_data_dir(req) == READ ? MMC_BLK_READ : MMC_BLK_WRITE;

	mmc_blk_reset_success(mq->blkdata, type);
}