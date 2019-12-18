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
struct TYPE_5__ {int num_sge; int /*<<< orphan*/  flags; TYPE_1__* sge; int /*<<< orphan*/  opcode; int /*<<< orphan*/  id; } ;
struct siw_wqe {int /*<<< orphan*/  wr_status; int /*<<< orphan*/ ** mem; scalar_t__ processed; int /*<<< orphan*/  bytes; TYPE_2__ sqe; } ;
struct siw_sqe {TYPE_3__* sge; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; int /*<<< orphan*/  id; } ;
struct siw_qp {int /*<<< orphan*/  rx_tagged; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  laddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  laddr; } ;

/* Variables and functions */
 int EPROTO ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int SIW_WQE_VALID ; 
 int /*<<< orphan*/  SIW_WR_INPROGRESS ; 
 struct siw_sqe* orq_get_current (struct siw_qp*) ; 
 struct siw_wqe* rx_wqe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int siw_orqe_start_rx(struct siw_qp *qp)
{
	struct siw_sqe *orqe;
	struct siw_wqe *wqe = NULL;

	/* make sure ORQ indices are current */
	smp_mb();

	orqe = orq_get_current(qp);
	if (READ_ONCE(orqe->flags) & SIW_WQE_VALID) {
		/* RRESP is a TAGGED RDMAP operation */
		wqe = rx_wqe(&qp->rx_tagged);
		wqe->sqe.id = orqe->id;
		wqe->sqe.opcode = orqe->opcode;
		wqe->sqe.sge[0].laddr = orqe->sge[0].laddr;
		wqe->sqe.sge[0].lkey = orqe->sge[0].lkey;
		wqe->sqe.sge[0].length = orqe->sge[0].length;
		wqe->sqe.flags = orqe->flags;
		wqe->sqe.num_sge = 1;
		wqe->bytes = orqe->sge[0].length;
		wqe->processed = 0;
		wqe->mem[0] = NULL;
		/* make sure WQE is completely written before valid */
		smp_wmb();
		wqe->wr_status = SIW_WR_INPROGRESS;

		return 0;
	}
	return -EPROTO;
}