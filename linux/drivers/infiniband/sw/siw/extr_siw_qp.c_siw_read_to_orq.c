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
struct siw_sqe {int flags; int num_sge; TYPE_1__* sge; int /*<<< orphan*/  opcode; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  laddr; } ;

/* Variables and functions */
 int SIW_WQE_VALID ; 

void siw_read_to_orq(struct siw_sqe *rreq, struct siw_sqe *sqe)
{
	rreq->id = sqe->id;
	rreq->opcode = sqe->opcode;
	rreq->sge[0].laddr = sqe->sge[0].laddr;
	rreq->sge[0].length = sqe->sge[0].length;
	rreq->sge[0].lkey = sqe->sge[0].lkey;
	rreq->sge[1].lkey = sqe->sge[1].lkey;
	rreq->flags = sqe->flags | SIW_WQE_VALID;
	rreq->num_sge = 1;
}