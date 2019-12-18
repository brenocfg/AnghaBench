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
struct TYPE_2__ {scalar_t__ queue; } ;
struct rxe_srq {struct rxe_srq* pd; TYPE_1__ rq; } ;
struct ib_udata {int dummy; } ;
struct ib_srq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_srq*) ; 
 int /*<<< orphan*/  rxe_queue_cleanup (scalar_t__) ; 
 struct rxe_srq* to_rsrq (struct ib_srq*) ; 

__attribute__((used)) static void rxe_destroy_srq(struct ib_srq *ibsrq, struct ib_udata *udata)
{
	struct rxe_srq *srq = to_rsrq(ibsrq);

	if (srq->rq.queue)
		rxe_queue_cleanup(srq->rq.queue);

	rxe_drop_ref(srq->pd);
	rxe_drop_ref(srq);
}