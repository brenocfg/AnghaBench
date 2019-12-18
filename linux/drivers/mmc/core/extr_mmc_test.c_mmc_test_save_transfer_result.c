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
struct timespec64 {int dummy; } ;
struct mmc_test_transfer_result {unsigned int count; unsigned int sectors; unsigned int rate; unsigned int iops; int /*<<< orphan*/  link; struct timespec64 ts; } ;
struct mmc_test_card {TYPE_1__* gr; } ;
struct TYPE_2__ {int /*<<< orphan*/  tr_lst; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mmc_test_transfer_result* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmc_test_save_transfer_result(struct mmc_test_card *test,
	unsigned int count, unsigned int sectors, struct timespec64 ts,
	unsigned int rate, unsigned int iops)
{
	struct mmc_test_transfer_result *tr;

	if (!test->gr)
		return;

	tr = kmalloc(sizeof(*tr), GFP_KERNEL);
	if (!tr)
		return;

	tr->count = count;
	tr->sectors = sectors;
	tr->ts = ts;
	tr->rate = rate;
	tr->iops = iops;

	list_add_tail(&tr->link, &test->gr->tr_lst);
}