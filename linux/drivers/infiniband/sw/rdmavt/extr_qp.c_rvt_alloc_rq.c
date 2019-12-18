#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct rvt_rwq {int dummy; } ;
struct rvt_rq {TYPE_1__* kwq; TYPE_2__* wq; } ;
struct rvt_krwq {int dummy; } ;
struct ib_udata {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  wq; } ;
struct TYPE_4__ {int /*<<< orphan*/  c_lock; int /*<<< orphan*/  p_lock; int /*<<< orphan*/  wq; int /*<<< orphan*/  curr_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvt_free_rq (struct rvt_rq*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* vmalloc_user (scalar_t__) ; 
 TYPE_1__* vzalloc_node (scalar_t__,int) ; 

int rvt_alloc_rq(struct rvt_rq *rq, u32 size, int node,
		 struct ib_udata *udata)
{
	if (udata) {
		rq->wq = vmalloc_user(sizeof(struct rvt_rwq) + size);
		if (!rq->wq)
			goto bail;
		/* need kwq with no buffers */
		rq->kwq = kzalloc_node(sizeof(*rq->kwq), GFP_KERNEL, node);
		if (!rq->kwq)
			goto bail;
		rq->kwq->curr_wq = rq->wq->wq;
	} else {
		/* need kwq with buffers */
		rq->kwq =
			vzalloc_node(sizeof(struct rvt_krwq) + size, node);
		if (!rq->kwq)
			goto bail;
		rq->kwq->curr_wq = rq->kwq->wq;
	}

	spin_lock_init(&rq->kwq->p_lock);
	spin_lock_init(&rq->kwq->c_lock);
	return 0;
bail:
	rvt_free_rq(rq);
	return -ENOMEM;
}