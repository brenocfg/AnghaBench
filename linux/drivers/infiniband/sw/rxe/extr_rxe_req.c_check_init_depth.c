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
struct rxe_send_wqe {int has_rd_atomic; } ;
struct TYPE_2__ {int need_rd_atomic; int /*<<< orphan*/  rd_atomic; } ;
struct rxe_qp {TYPE_1__ req; } ;

/* Variables and functions */
 int EAGAIN ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int check_init_depth(struct rxe_qp *qp, struct rxe_send_wqe *wqe)
{
	int depth;

	if (wqe->has_rd_atomic)
		return 0;

	qp->req.need_rd_atomic = 1;
	depth = atomic_dec_return(&qp->req.rd_atomic);

	if (depth >= 0) {
		qp->req.need_rd_atomic = 0;
		wqe->has_rd_atomic = 1;
		return 0;
	}

	atomic_inc(&qp->req.rd_atomic);
	return -EAGAIN;
}