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
struct rdma_cqe_requester {int flags; } ;
union rdma_cqe {struct rdma_cqe_requester req; } ;
struct qedr_cq {int pbl_toggle; } ;

/* Variables and functions */
 int RDMA_CQE_REQUESTER_TOGGLE_BIT_MASK ; 

__attribute__((used)) static int is_valid_cqe(struct qedr_cq *cq, union rdma_cqe *cqe)
{
	struct rdma_cqe_requester *resp_cqe = &cqe->req;

	return (resp_cqe->flags & RDMA_CQE_REQUESTER_TOGGLE_BIT_MASK) ==
		cq->pbl_toggle;
}