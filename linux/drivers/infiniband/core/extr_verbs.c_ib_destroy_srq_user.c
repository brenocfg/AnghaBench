#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ib_udata {int dummy; } ;
struct TYPE_10__ {TYPE_2__* xrcd; } ;
struct TYPE_12__ {TYPE_4__* cq; TYPE_3__ xrc; } ;
struct ib_srq {scalar_t__ srq_type; TYPE_5__ ext; TYPE_1__* pd; TYPE_7__* device; int /*<<< orphan*/  usecnt; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* destroy_srq ) (struct ib_srq*,struct ib_udata*) ;} ;
struct TYPE_14__ {TYPE_6__ ops; } ;
struct TYPE_11__ {int /*<<< orphan*/  usecnt; } ;
struct TYPE_9__ {int /*<<< orphan*/  usecnt; } ;
struct TYPE_8__ {int /*<<< orphan*/  usecnt; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IB_SRQT_XRC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ ib_srq_has_cq (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ib_srq*) ; 
 int /*<<< orphan*/  stub1 (struct ib_srq*,struct ib_udata*) ; 

int ib_destroy_srq_user(struct ib_srq *srq, struct ib_udata *udata)
{
	if (atomic_read(&srq->usecnt))
		return -EBUSY;

	srq->device->ops.destroy_srq(srq, udata);

	atomic_dec(&srq->pd->usecnt);
	if (srq->srq_type == IB_SRQT_XRC)
		atomic_dec(&srq->ext.xrc.xrcd->usecnt);
	if (ib_srq_has_cq(srq->srq_type))
		atomic_dec(&srq->ext.cq->usecnt);
	kfree(srq);

	return 0;
}