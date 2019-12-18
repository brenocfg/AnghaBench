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
struct mmc_test_card {TYPE_2__* card; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int max_blk_count; } ;

/* Variables and functions */
 int RESULT_UNSUP_HOST ; 
 int mmc_test_broken_transfer (struct mmc_test_card*,int,int,int) ; 
 int mmc_test_set_blksize (struct mmc_test_card*,int) ; 

__attribute__((used)) static int mmc_test_multi_xfersize_write(struct mmc_test_card *test)
{
	int ret;

	if (test->card->host->max_blk_count == 1)
		return RESULT_UNSUP_HOST;

	ret = mmc_test_set_blksize(test, 512);
	if (ret)
		return ret;

	return mmc_test_broken_transfer(test, 2, 512, 1);
}