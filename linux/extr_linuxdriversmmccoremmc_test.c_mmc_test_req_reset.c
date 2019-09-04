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
struct TYPE_2__ {int /*<<< orphan*/ * stop; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cmd; } ;
struct mmc_test_req {int /*<<< orphan*/  stop; TYPE_1__ mrq; int /*<<< orphan*/  data; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mmc_test_req*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mmc_test_req_reset(struct mmc_test_req *rq)
{
	memset(rq, 0, sizeof(struct mmc_test_req));

	rq->mrq.cmd = &rq->cmd;
	rq->mrq.data = &rq->data;
	rq->mrq.stop = &rq->stop;
}