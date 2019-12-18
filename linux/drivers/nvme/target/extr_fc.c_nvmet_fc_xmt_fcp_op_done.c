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
struct nvmet_fc_fcp_iod {int dummy; } ;
struct nvmefc_tgt_fcp_req {struct nvmet_fc_fcp_iod* nvmet_fc_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvmet_fc_fod_op_done (struct nvmet_fc_fcp_iod*) ; 

__attribute__((used)) static void
nvmet_fc_xmt_fcp_op_done(struct nvmefc_tgt_fcp_req *fcpreq)
{
	struct nvmet_fc_fcp_iod *fod = fcpreq->nvmet_fc_private;

	nvmet_fc_fod_op_done(fod);
}