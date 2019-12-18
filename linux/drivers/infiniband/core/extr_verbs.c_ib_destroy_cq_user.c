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
struct ib_udata {int dummy; } ;
struct ib_cq {TYPE_2__* device; int /*<<< orphan*/  res; int /*<<< orphan*/  usecnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy_cq ) (struct ib_cq*,struct ib_udata*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_cq*) ; 
 int /*<<< orphan*/  rdma_restrack_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ib_cq*,struct ib_udata*) ; 

int ib_destroy_cq_user(struct ib_cq *cq, struct ib_udata *udata)
{
	if (atomic_read(&cq->usecnt))
		return -EBUSY;

	rdma_restrack_del(&cq->res);
	cq->device->ops.destroy_cq(cq, udata);
	kfree(cq);
	return 0;
}