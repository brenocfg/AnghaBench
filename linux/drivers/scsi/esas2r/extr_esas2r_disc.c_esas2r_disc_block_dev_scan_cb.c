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
struct TYPE_3__ {int /*<<< orphan*/  scan_generation; } ;
struct TYPE_4__ {TYPE_1__ mgt_rsp; } ;
struct esas2r_request {scalar_t__ req_stat; TYPE_2__ func_rsp; scalar_t__ interrupt_cx; } ;
struct esas2r_disc_context {int flags; scalar_t__ raid_grp_ix; int /*<<< orphan*/  state; int /*<<< orphan*/  scan_gen; } ;
struct esas2r_adapter {int /*<<< orphan*/  mem_lock; } ;

/* Variables and functions */
 int DCF_POLLED ; 
 int /*<<< orphan*/  DCS_RAID_GRP_INFO ; 
 scalar_t__ RS_SUCCESS ; 
 int /*<<< orphan*/  esas2r_disc_continue (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_rq_destroy_request (struct esas2r_request*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void esas2r_disc_block_dev_scan_cb(struct esas2r_adapter *a,
					  struct esas2r_request *rq)
{
	struct esas2r_disc_context *dc =
		(struct esas2r_disc_context *)rq->interrupt_cx;
	unsigned long flags;

	esas2r_trace_enter();

	spin_lock_irqsave(&a->mem_lock, flags);

	if (rq->req_stat == RS_SUCCESS)
		dc->scan_gen = rq->func_rsp.mgt_rsp.scan_generation;

	dc->state = DCS_RAID_GRP_INFO;
	dc->raid_grp_ix = 0;

	esas2r_rq_destroy_request(rq, a);

	/* continue discovery if it's interrupt driven */

	if (!(dc->flags & DCF_POLLED))
		esas2r_disc_continue(a, rq);

	spin_unlock_irqrestore(&a->mem_lock, flags);

	esas2r_trace_exit();
}