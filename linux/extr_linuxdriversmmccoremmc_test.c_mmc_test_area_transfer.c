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
struct mmc_test_area {int /*<<< orphan*/  blocks; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct mmc_test_card {struct mmc_test_area area; } ;

/* Variables and functions */
 int mmc_test_simple_transfer (struct mmc_test_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mmc_test_area_transfer(struct mmc_test_card *test,
				  unsigned int dev_addr, int write)
{
	struct mmc_test_area *t = &test->area;

	return mmc_test_simple_transfer(test, t->sg, t->sg_len, dev_addr,
					t->blocks, 512, write);
}