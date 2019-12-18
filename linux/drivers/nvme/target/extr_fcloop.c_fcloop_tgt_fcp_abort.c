#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvmet_fc_target_port {int dummy; } ;
struct nvmefc_tgt_fcp_req {int dummy; } ;
struct fcloop_fcpreq {int aborted; int /*<<< orphan*/  status; int /*<<< orphan*/  reqlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_SC_INTERNAL ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct fcloop_fcpreq* tgt_fcp_req_to_fcpreq (struct nvmefc_tgt_fcp_req*) ; 

__attribute__((used)) static void
fcloop_tgt_fcp_abort(struct nvmet_fc_target_port *tgtport,
			struct nvmefc_tgt_fcp_req *tgt_fcpreq)
{
	struct fcloop_fcpreq *tfcp_req = tgt_fcp_req_to_fcpreq(tgt_fcpreq);

	/*
	 * mark aborted only in case there were 2 threads in transport
	 * (one doing io, other doing abort) and only kills ops posted
	 * after the abort request
	 */
	spin_lock_irq(&tfcp_req->reqlock);
	tfcp_req->aborted = true;
	spin_unlock_irq(&tfcp_req->reqlock);

	tfcp_req->status = NVME_SC_INTERNAL;

	/*
	 * nothing more to do. If io wasn't active, the transport should
	 * immediately call the req_release. If it was active, the op
	 * will complete, and the lldd should call req_release.
	 */
}