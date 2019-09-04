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
struct ib_cq {TYPE_1__* device; int /*<<< orphan*/  res; int /*<<< orphan*/  usecnt; } ;
struct TYPE_2__ {int (* destroy_cq ) (struct ib_cq*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_del (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_cq*) ; 

int ib_destroy_cq(struct ib_cq *cq)
{
	if (atomic_read(&cq->usecnt))
		return -EBUSY;

	rdma_restrack_del(&cq->res);
	return cq->device->destroy_cq(cq);
}