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
struct TYPE_2__ {void* all; void* count; scalar_t__ lock; void* status; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,void*) ;scalar_t__ timer_active; struct bfa_diag_qtest_result_s* result; } ;
struct bfa_fcdiag_s {TYPE_1__ qtest; } ;
struct bfa_diag_qtest_result_s {void* count; void* queue; void* status; } ;

/* Variables and functions */
 void* BFA_STATUS_ETIMER ; 
 void* QTEST_CNT_DEFAULT ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fcdiag_s*,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
bfa_fcdiag_queuetest_timeout(void *cbarg)
{
	struct bfa_fcdiag_s       *fcdiag = cbarg;
	struct bfa_diag_qtest_result_s *res = fcdiag->qtest.result;

	bfa_trc(fcdiag, fcdiag->qtest.all);
	bfa_trc(fcdiag, fcdiag->qtest.count);

	fcdiag->qtest.timer_active = 0;

	res->status = BFA_STATUS_ETIMER;
	res->count  = QTEST_CNT_DEFAULT - fcdiag->qtest.count;
	if (fcdiag->qtest.all)
		res->queue  = fcdiag->qtest.all;

	bfa_trc(fcdiag, BFA_STATUS_ETIMER);
	fcdiag->qtest.status = BFA_STATUS_ETIMER;
	fcdiag->qtest.cbfn(fcdiag->qtest.cbarg, fcdiag->qtest.status);
	fcdiag->qtest.lock = 0;
}