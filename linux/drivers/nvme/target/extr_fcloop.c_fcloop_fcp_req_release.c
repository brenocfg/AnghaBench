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
struct fcloop_fcpreq {int /*<<< orphan*/  tio_done_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct fcloop_fcpreq* tgt_fcp_req_to_fcpreq (struct nvmefc_tgt_fcp_req*) ; 

__attribute__((used)) static void
fcloop_fcp_req_release(struct nvmet_fc_target_port *tgtport,
			struct nvmefc_tgt_fcp_req *tgt_fcpreq)
{
	struct fcloop_fcpreq *tfcp_req = tgt_fcp_req_to_fcpreq(tgt_fcpreq);

	schedule_work(&tfcp_req->tio_done_work);
}