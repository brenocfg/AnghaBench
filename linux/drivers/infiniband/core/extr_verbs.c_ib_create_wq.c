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
struct ib_wq_init_attr {TYPE_3__* cq; int /*<<< orphan*/  wq_type; int /*<<< orphan*/  wq_context; int /*<<< orphan*/  event_handler; } ;
struct ib_wq {int /*<<< orphan*/  usecnt; int /*<<< orphan*/ * uobject; struct ib_pd* pd; TYPE_2__* device; TYPE_3__* cq; int /*<<< orphan*/  wq_type; int /*<<< orphan*/  wq_context; int /*<<< orphan*/  event_handler; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  usecnt; } ;
struct TYPE_4__ {struct ib_wq* (* create_wq ) (struct ib_pd*,struct ib_wq_init_attr*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct ib_wq* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct ib_wq*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_wq* stub1 (struct ib_pd*,struct ib_wq_init_attr*,int /*<<< orphan*/ *) ; 

struct ib_wq *ib_create_wq(struct ib_pd *pd,
			   struct ib_wq_init_attr *wq_attr)
{
	struct ib_wq *wq;

	if (!pd->device->ops.create_wq)
		return ERR_PTR(-EOPNOTSUPP);

	wq = pd->device->ops.create_wq(pd, wq_attr, NULL);
	if (!IS_ERR(wq)) {
		wq->event_handler = wq_attr->event_handler;
		wq->wq_context = wq_attr->wq_context;
		wq->wq_type = wq_attr->wq_type;
		wq->cq = wq_attr->cq;
		wq->device = pd->device;
		wq->pd = pd;
		wq->uobject = NULL;
		atomic_inc(&pd->usecnt);
		atomic_inc(&wq_attr->cq->usecnt);
		atomic_set(&wq->usecnt, 0);
	}
	return wq;
}