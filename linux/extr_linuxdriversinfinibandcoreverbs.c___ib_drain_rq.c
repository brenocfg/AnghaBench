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
struct ib_recv_wr {TYPE_1__* wr_cqe; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct ib_qp {struct ib_cq* recv_cq; } ;
struct TYPE_2__ {int /*<<< orphan*/  done; } ;
struct ib_drain_cqe {int /*<<< orphan*/  done; TYPE_1__ cqe; } ;
struct ib_cq {scalar_t__ poll_ctx; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ IB_POLL_DIRECT ; 
 int /*<<< orphan*/  IB_QPS_ERR ; 
 int /*<<< orphan*/  IB_QP_STATE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  ib_drain_qp_done ; 
 int ib_modify_qp (struct ib_qp*,struct ib_qp_attr*,int /*<<< orphan*/ ) ; 
 int ib_post_recv (struct ib_qp*,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_process_cq_direct (struct ib_cq*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void __ib_drain_rq(struct ib_qp *qp)
{
	struct ib_cq *cq = qp->recv_cq;
	struct ib_qp_attr attr = { .qp_state = IB_QPS_ERR };
	struct ib_drain_cqe rdrain;
	struct ib_recv_wr rwr = {};
	int ret;

	ret = ib_modify_qp(qp, &attr, IB_QP_STATE);
	if (ret) {
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		return;
	}

	rwr.wr_cqe = &rdrain.cqe;
	rdrain.cqe.done = ib_drain_qp_done;
	init_completion(&rdrain.done);

	ret = ib_post_recv(qp, &rwr, NULL);
	if (ret) {
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		return;
	}

	if (cq->poll_ctx == IB_POLL_DIRECT)
		while (wait_for_completion_timeout(&rdrain.done, HZ / 10) <= 0)
			ib_process_cq_direct(cq, -1);
	else
		wait_for_completion(&rdrain.done);
}