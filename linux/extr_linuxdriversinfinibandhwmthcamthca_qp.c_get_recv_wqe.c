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
struct TYPE_8__ {int wqe_shift; } ;
struct TYPE_5__ {void* buf; } ;
struct TYPE_7__ {TYPE_2__* page_list; TYPE_1__ direct; } ;
struct mthca_qp {TYPE_4__ rq; TYPE_3__ queue; scalar_t__ is_direct; } ;
struct TYPE_6__ {void* buf; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 

__attribute__((used)) static void *get_recv_wqe(struct mthca_qp *qp, int n)
{
	if (qp->is_direct)
		return qp->queue.direct.buf + (n << qp->rq.wqe_shift);
	else
		return qp->queue.page_list[(n << qp->rq.wqe_shift) >> PAGE_SHIFT].buf +
			((n << qp->rq.wqe_shift) & (PAGE_SIZE - 1));
}