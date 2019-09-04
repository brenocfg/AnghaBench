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
struct mmc_test_area {unsigned long blocks; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  max_seg_sz; int /*<<< orphan*/  max_segs; int /*<<< orphan*/  sg; int /*<<< orphan*/  mem; } ;
struct mmc_test_card {TYPE_1__* card; struct mmc_test_area area; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int mmc_test_map_sg (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mmc_test_map_sg_max_scatter (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_test_area_map(struct mmc_test_card *test, unsigned long sz,
			     int max_scatter, int min_sg_len)
{
	struct mmc_test_area *t = &test->area;
	int err;

	t->blocks = sz >> 9;

	if (max_scatter) {
		err = mmc_test_map_sg_max_scatter(t->mem, sz, t->sg,
						  t->max_segs, t->max_seg_sz,
				       &t->sg_len);
	} else {
		err = mmc_test_map_sg(t->mem, sz, t->sg, 1, t->max_segs,
				      t->max_seg_sz, &t->sg_len, min_sg_len);
	}
	if (err)
		pr_info("%s: Failed to map sg list\n",
		       mmc_hostname(test->card->host));
	return err;
}