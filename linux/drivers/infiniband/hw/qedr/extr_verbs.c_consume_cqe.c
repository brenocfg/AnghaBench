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
struct qedr_cq {scalar_t__ latest_cqe; scalar_t__ toggle_cqe; int /*<<< orphan*/  pbl; int /*<<< orphan*/  pbl_toggle; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_CQE_REQUESTER_TOGGLE_BIT_MASK ; 
 scalar_t__ qed_chain_consume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void consume_cqe(struct qedr_cq *cq)
{
	if (cq->latest_cqe == cq->toggle_cqe)
		cq->pbl_toggle ^= RDMA_CQE_REQUESTER_TOGGLE_BIT_MASK;

	cq->latest_cqe = qed_chain_consume(&cq->pbl);
}