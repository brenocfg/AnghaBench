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
struct ib_qp {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* drain_rq ) (struct ib_qp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __ib_drain_rq (struct ib_qp*) ; 
 int /*<<< orphan*/  stub1 (struct ib_qp*) ; 

void ib_drain_rq(struct ib_qp *qp)
{
	if (qp->device->drain_rq)
		qp->device->drain_rq(qp);
	else
		__ib_drain_rq(qp);
}