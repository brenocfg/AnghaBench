#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  max_cnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_cnt; } ;
struct ocrdma_qp {int /*<<< orphan*/ * rqe_wr_id_tbl; TYPE_2__ rq; int /*<<< orphan*/ * wqe_wr_id_tbl; TYPE_1__ sq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocrdma_alloc_wr_id_tbl(struct ocrdma_qp *qp)
{
	qp->wqe_wr_id_tbl =
	    kcalloc(qp->sq.max_cnt, sizeof(*(qp->wqe_wr_id_tbl)),
		    GFP_KERNEL);
	if (qp->wqe_wr_id_tbl == NULL)
		return -ENOMEM;
	qp->rqe_wr_id_tbl =
	    kcalloc(qp->rq.max_cnt, sizeof(u64), GFP_KERNEL);
	if (qp->rqe_wr_id_tbl == NULL)
		return -ENOMEM;

	return 0;
}