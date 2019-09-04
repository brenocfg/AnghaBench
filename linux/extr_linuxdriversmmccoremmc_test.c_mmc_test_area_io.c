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
 int mmc_test_area_io_seq (struct mmc_test_card*,unsigned long,unsigned int,int,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_test_area_io(struct mmc_test_card *test, unsigned long sz,
			    unsigned int dev_addr, int write, int max_scatter,
			    int timed)
{
	return mmc_test_area_io_seq(test, sz, dev_addr, write, max_scatter,
				    timed, 1, false, 0);
}