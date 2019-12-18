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
struct qed_rdma_query_qp_out_params {int /*<<< orphan*/  state; } ;
struct qed_rdma_qp {int /*<<< orphan*/  iwarp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_iwarp2roce_state (int /*<<< orphan*/ ) ; 

void
qed_iwarp_query_qp(struct qed_rdma_qp *qp,
		   struct qed_rdma_query_qp_out_params *out_params)
{
	out_params->state = qed_iwarp2roce_state(qp->iwarp_state);
}