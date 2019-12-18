#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct TYPE_7__ {void* private; } ;
struct TYPE_8__ {scalar_t__ command_id; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_4__ common; } ;
struct nvme_fc_cmd_iu {struct nvme_command sqe; } ;
struct nvme_fc_fcp_op {TYPE_3__ fcp_req; int /*<<< orphan*/  flags; struct nvme_fc_cmd_iu cmd_iu; } ;
struct nvme_fc_ctrl {int /*<<< orphan*/ * queues; TYPE_2__* lport; struct nvme_fc_fcp_op* aen_ops; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  fcprqst_priv_sz; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FCOP_FLAGS_AEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NVME_AQ_BLK_MQ_DEPTH ; 
 int NVME_NR_AEN_COMMANDS ; 
 int __nvme_fc_init_request (struct nvme_fc_ctrl*,int /*<<< orphan*/ *,struct nvme_fc_fcp_op*,struct request*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_admin_async_event ; 

__attribute__((used)) static int
nvme_fc_init_aen_ops(struct nvme_fc_ctrl *ctrl)
{
	struct nvme_fc_fcp_op *aen_op;
	struct nvme_fc_cmd_iu *cmdiu;
	struct nvme_command *sqe;
	void *private;
	int i, ret;

	aen_op = ctrl->aen_ops;
	for (i = 0; i < NVME_NR_AEN_COMMANDS; i++, aen_op++) {
		private = kzalloc(ctrl->lport->ops->fcprqst_priv_sz,
						GFP_KERNEL);
		if (!private)
			return -ENOMEM;

		cmdiu = &aen_op->cmd_iu;
		sqe = &cmdiu->sqe;
		ret = __nvme_fc_init_request(ctrl, &ctrl->queues[0],
				aen_op, (struct request *)NULL,
				(NVME_AQ_BLK_MQ_DEPTH + i));
		if (ret) {
			kfree(private);
			return ret;
		}

		aen_op->flags = FCOP_FLAGS_AEN;
		aen_op->fcp_req.private = private;

		memset(sqe, 0, sizeof(*sqe));
		sqe->common.opcode = nvme_admin_async_event;
		/* Note: core layer may overwrite the sqe.command_id value */
		sqe->common.command_id = NVME_AQ_BLK_MQ_DEPTH + i;
	}
	return 0;
}