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
struct TYPE_2__ {int /*<<< orphan*/ * private; } ;
struct nvme_fc_fcp_op {TYPE_1__ fcp_req; } ;
struct nvme_fc_ctrl {struct nvme_fc_fcp_op* aen_ops; } ;

/* Variables and functions */
 int NVME_NR_AEN_COMMANDS ; 
 int /*<<< orphan*/  __nvme_fc_exit_request (struct nvme_fc_ctrl*,struct nvme_fc_fcp_op*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvme_fc_term_aen_ops(struct nvme_fc_ctrl *ctrl)
{
	struct nvme_fc_fcp_op *aen_op;
	int i;

	aen_op = ctrl->aen_ops;
	for (i = 0; i < NVME_NR_AEN_COMMANDS; i++, aen_op++) {
		if (!aen_op->fcp_req.private)
			continue;

		__nvme_fc_exit_request(ctrl, aen_op);

		kfree(aen_op->fcp_req.private);
		aen_op->fcp_req.private = NULL;
	}
}