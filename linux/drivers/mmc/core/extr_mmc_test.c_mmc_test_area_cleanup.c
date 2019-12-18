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
struct mmc_test_area {int /*<<< orphan*/  mem; int /*<<< orphan*/  sg; } ;
struct mmc_test_card {struct mmc_test_area area; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_test_free_mem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_test_area_cleanup(struct mmc_test_card *test)
{
	struct mmc_test_area *t = &test->area;

	kfree(t->sg);
	mmc_test_free_mem(t->mem);

	return 0;
}