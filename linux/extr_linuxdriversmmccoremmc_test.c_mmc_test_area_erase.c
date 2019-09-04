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
struct mmc_test_area {int max_sz; int /*<<< orphan*/  dev_addr; } ;
struct mmc_test_card {int /*<<< orphan*/  card; struct mmc_test_area area; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_ERASE_ARG ; 
 int /*<<< orphan*/  mmc_can_erase (int /*<<< orphan*/ ) ; 
 int mmc_erase (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_test_area_erase(struct mmc_test_card *test)
{
	struct mmc_test_area *t = &test->area;

	if (!mmc_can_erase(test->card))
		return 0;

	return mmc_erase(test->card, t->dev_addr, t->max_sz >> 9,
			 MMC_ERASE_ARG);
}