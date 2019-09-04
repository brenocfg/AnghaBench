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
struct mmc_test_multiple_rw {int len; int /*<<< orphan*/ * sg_len; int /*<<< orphan*/  size; } ;
struct mmc_test_card {int dummy; } ;

/* Variables and functions */
 int mmc_test_rw_multiple (struct mmc_test_card*,struct mmc_test_multiple_rw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_test_rw_multiple_sg_len(struct mmc_test_card *test,
				       struct mmc_test_multiple_rw *rw)
{
	int ret = 0;
	int i;

	for (i = 0 ; i < rw->len && ret == 0; i++) {
		ret = mmc_test_rw_multiple(test, rw, 512 * 1024, rw->size,
					   rw->sg_len[i]);
		if (ret)
			break;
	}
	return ret;
}