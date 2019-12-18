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
struct nvmet_fc_tgtport {int dummy; } ;
struct nvmet_fc_fcp_iod {int /*<<< orphan*/  req; struct nvmet_fc_tgtport* tgtport; struct nvmefc_tgt_fcp_req* fcpreq; } ;
struct nvmefc_tgt_fcp_req {scalar_t__ op; } ;

/* Variables and functions */
 scalar_t__ NVMET_FCOP_WRITEDATA ; 
 int /*<<< orphan*/  NVME_SC_INTERNAL ; 
 int /*<<< orphan*/  nvmet_fc_abort_op (struct nvmet_fc_tgtport*,struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  nvmet_req_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
__nvmet_fc_fod_op_abort(struct nvmet_fc_fcp_iod *fod, bool abort)
{
	struct nvmefc_tgt_fcp_req *fcpreq = fod->fcpreq;
	struct nvmet_fc_tgtport *tgtport = fod->tgtport;

	/* if in the middle of an io and we need to tear down */
	if (abort) {
		if (fcpreq->op == NVMET_FCOP_WRITEDATA) {
			nvmet_req_complete(&fod->req, NVME_SC_INTERNAL);
			return true;
		}

		nvmet_fc_abort_op(tgtport, fod);
		return true;
	}

	return false;
}