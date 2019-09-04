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
struct mmc_test_multiple_rw {unsigned int* bs; int do_write; int do_nonblock_req; int /*<<< orphan*/  prepare; int /*<<< orphan*/  len; int /*<<< orphan*/  size; } ;
struct mmc_test_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  MMC_TEST_PREP_ERASE ; 
 int /*<<< orphan*/  TEST_AREA_MAX_SIZE ; 
 int mmc_test_rw_multiple_size (struct mmc_test_card*,struct mmc_test_multiple_rw*) ; 

__attribute__((used)) static int mmc_test_profile_mult_write_blocking_perf(struct mmc_test_card *test)
{
	unsigned int bs[] = {1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16,
			     1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 22};
	struct mmc_test_multiple_rw test_data = {
		.bs = bs,
		.size = TEST_AREA_MAX_SIZE,
		.len = ARRAY_SIZE(bs),
		.do_write = true,
		.do_nonblock_req = false,
		.prepare = MMC_TEST_PREP_ERASE,
	};

	return mmc_test_rw_multiple_size(test, &test_data);
}