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
struct TYPE_2__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct rdma_cqe_requester {TYPE_1__ qp_handle; } ;
union rdma_cqe {struct rdma_cqe_requester req; } ;
struct qedr_qp {int dummy; } ;

/* Variables and functions */
 scalar_t__ HILO_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static struct qedr_qp *cqe_get_qp(union rdma_cqe *cqe)
{
	struct rdma_cqe_requester *resp_cqe = &cqe->req;
	struct qedr_qp *qp;

	qp = (struct qedr_qp *)(uintptr_t)HILO_GEN(resp_cqe->qp_handle.hi,
						   resp_cqe->qp_handle.lo,
						   u64);
	return qp;
}