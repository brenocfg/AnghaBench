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
struct nvme_fc_fcp_op {int flags; } ;
struct nvme_fc_ctrl {struct nvme_fc_fcp_op* aen_ops; } ;

/* Variables and functions */
 int FCOP_FLAGS_AEN ; 
 int NVME_NR_AEN_COMMANDS ; 
 int /*<<< orphan*/  __nvme_fc_abort_op (struct nvme_fc_ctrl*,struct nvme_fc_fcp_op*) ; 

__attribute__((used)) static void
nvme_fc_abort_aen_ops(struct nvme_fc_ctrl *ctrl)
{
	struct nvme_fc_fcp_op *aen_op = ctrl->aen_ops;
	int i;

	/* ensure we've initialized the ops once */
	if (!(aen_op->flags & FCOP_FLAGS_AEN))
		return;

	for (i = 0; i < NVME_NR_AEN_COMMANDS; i++, aen_op++)
		__nvme_fc_abort_op(ctrl, aen_op);
}