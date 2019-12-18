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
struct nvmet_fc_tgtport {int /*<<< orphan*/  fc_target_port; TYPE_1__* ops; } ;
struct nvmet_fc_fcp_iod {int /*<<< orphan*/  queue; int /*<<< orphan*/  aborted; struct nvmefc_tgt_fcp_req* fcpreq; } ;
struct nvmefc_tgt_fcp_req {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fcp_abort ) (int /*<<< orphan*/ *,struct nvmefc_tgt_fcp_req*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvmet_fc_free_fcp_iod (int /*<<< orphan*/ ,struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  nvmet_fc_free_tgt_pgs (struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct nvmefc_tgt_fcp_req*) ; 

__attribute__((used)) static void
nvmet_fc_abort_op(struct nvmet_fc_tgtport *tgtport,
				struct nvmet_fc_fcp_iod *fod)
{
	struct nvmefc_tgt_fcp_req *fcpreq = fod->fcpreq;

	/* data no longer needed */
	nvmet_fc_free_tgt_pgs(fod);

	/*
	 * if an ABTS was received or we issued the fcp_abort early
	 * don't call abort routine again.
	 */
	/* no need to take lock - lock was taken earlier to get here */
	if (!fod->aborted)
		tgtport->ops->fcp_abort(&tgtport->fc_target_port, fcpreq);

	nvmet_fc_free_fcp_iod(fod->queue, fod);
}