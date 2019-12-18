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
struct ib_wq {TYPE_2__* device; int /*<<< orphan*/  usecnt; struct ib_pd* pd; struct ib_cq* cq; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; } ;
struct ib_cq {int /*<<< orphan*/  usecnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy_wq ) (struct ib_wq*,struct ib_udata*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ib_wq*,struct ib_udata*) ; 

int ib_destroy_wq(struct ib_wq *wq, struct ib_udata *udata)
{
	struct ib_cq *cq = wq->cq;
	struct ib_pd *pd = wq->pd;

	if (atomic_read(&wq->usecnt))
		return -EBUSY;

	wq->device->ops.destroy_wq(wq, udata);
	atomic_dec(&pd->usecnt);
	atomic_dec(&cq->usecnt);

	return 0;
}