#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_11__ {TYPE_6__* qp; TYPE_3__* dev; } ;
struct c4iw_ep {TYPE_5__ com; } ;
typedef  enum chip_type { ____Placeholder_chip_type } chip_type ;
struct TYPE_10__ {scalar_t__ uobject; } ;
struct TYPE_12__ {int /*<<< orphan*/  wq; TYPE_4__ ibqp; } ;
struct TYPE_7__ {int adapter_type; } ;
struct TYPE_8__ {TYPE_1__ lldi; } ;
struct TYPE_9__ {TYPE_2__ rdev; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int) ; 
 scalar_t__ CHELSIO_T5 ; 
 int /*<<< orphan*/  c4iw_flush_srqidx (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  t4_set_wq_in_error (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void complete_cached_srq_buffers(struct c4iw_ep *ep, u32 srqidx)
{
	enum chip_type adapter_type;

	adapter_type = ep->com.dev->rdev.lldi.adapter_type;

	/*
	 * If this TCB had a srq buffer cached, then we must complete
	 * it. For user mode, that means saving the srqidx in the
	 * user/kernel status page for this qp.  For kernel mode, just
	 * synthesize the CQE now.
	 */
	if (CHELSIO_CHIP_VERSION(adapter_type) > CHELSIO_T5 && srqidx) {
		if (ep->com.qp->ibqp.uobject)
			t4_set_wq_in_error(&ep->com.qp->wq, srqidx);
		else
			c4iw_flush_srqidx(ep->com.qp, srqidx);
	}
}