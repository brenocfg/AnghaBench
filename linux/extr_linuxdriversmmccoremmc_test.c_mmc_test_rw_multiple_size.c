#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mmc_test_multiple_rw {int len; int /*<<< orphan*/  size; int /*<<< orphan*/ * bs; scalar_t__ do_nonblock_req; } ;
struct mmc_test_card {TYPE_3__* card; } ;
struct TYPE_6__ {TYPE_2__* host; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {void* post_req; void* pre_req; } ;

/* Variables and functions */
 int EINVAL ; 
 int mmc_test_rw_multiple (struct mmc_test_card*,struct mmc_test_multiple_rw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int mmc_test_rw_multiple_size(struct mmc_test_card *test,
				     struct mmc_test_multiple_rw *rw)
{
	int ret = 0;
	int i;
	void *pre_req = test->card->host->ops->pre_req;
	void *post_req = test->card->host->ops->post_req;

	if (rw->do_nonblock_req &&
	    ((!pre_req && post_req) || (pre_req && !post_req))) {
		pr_info("error: only one of pre/post is defined\n");
		return -EINVAL;
	}

	for (i = 0 ; i < rw->len && ret == 0; i++) {
		ret = mmc_test_rw_multiple(test, rw, rw->bs[i], rw->size, 0);
		if (ret)
			break;
	}
	return ret;
}