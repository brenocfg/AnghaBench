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
struct mmc_test_card {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int mmc_set_blocklen (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mmc_test_set_blksize(struct mmc_test_card *test, unsigned size)
{
	return mmc_set_blocklen(test->card, size);
}