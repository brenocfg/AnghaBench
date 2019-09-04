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
struct mmc_test_card {int dummy; } ;

/* Variables and functions */
 int mmc_test_broken_transfer (struct mmc_test_card*,int,int,int) ; 
 int mmc_test_set_blksize (struct mmc_test_card*,int) ; 

__attribute__((used)) static int mmc_test_xfersize_write(struct mmc_test_card *test)
{
	int ret;

	ret = mmc_test_set_blksize(test, 512);
	if (ret)
		return ret;

	return mmc_test_broken_transfer(test, 1, 512, 1);
}