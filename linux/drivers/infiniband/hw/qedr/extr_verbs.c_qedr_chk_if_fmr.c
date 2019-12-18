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
struct TYPE_8__ {size_t cons; } ;
struct qedr_qp {TYPE_4__ sq; TYPE_3__* wqe_wr_id; } ;
struct TYPE_7__ {scalar_t__ opcode; TYPE_2__* mr; } ;
struct TYPE_5__ {int /*<<< orphan*/  completed; } ;
struct TYPE_6__ {TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ IB_WC_REG_MR ; 

__attribute__((used)) static inline void qedr_chk_if_fmr(struct qedr_qp *qp)
{
	if (qp->wqe_wr_id[qp->sq.cons].opcode == IB_WC_REG_MR)
		qp->wqe_wr_id[qp->sq.cons].mr->info.completed++;
}