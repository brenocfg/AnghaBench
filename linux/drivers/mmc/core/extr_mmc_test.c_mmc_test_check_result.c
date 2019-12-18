#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mmc_test_card {int dummy; } ;
struct mmc_request {TYPE_4__* data; TYPE_3__* stop; TYPE_2__* cmd; TYPE_1__* sbc; } ;
struct TYPE_8__ {int error; int bytes_xfered; int blocks; int blksz; } ;
struct TYPE_7__ {int error; } ;
struct TYPE_6__ {int error; } ;
struct TYPE_5__ {int error; } ;

/* Variables and functions */
 int EINVAL ; 
 int RESULT_FAIL ; 
 int RESULT_UNSUP_HOST ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int mmc_test_check_result(struct mmc_test_card *test,
				 struct mmc_request *mrq)
{
	int ret;

	if (WARN_ON(!mrq || !mrq->cmd || !mrq->data))
		return -EINVAL;

	ret = 0;

	if (mrq->sbc && mrq->sbc->error)
		ret = mrq->sbc->error;
	if (!ret && mrq->cmd->error)
		ret = mrq->cmd->error;
	if (!ret && mrq->data->error)
		ret = mrq->data->error;
	if (!ret && mrq->stop && mrq->stop->error)
		ret = mrq->stop->error;
	if (!ret && mrq->data->bytes_xfered !=
		mrq->data->blocks * mrq->data->blksz)
		ret = RESULT_FAIL;

	if (ret == -EINVAL)
		ret = RESULT_UNSUP_HOST;

	return ret;
}