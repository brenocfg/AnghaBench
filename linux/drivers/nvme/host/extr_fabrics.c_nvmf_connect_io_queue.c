#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union nvme_result {int /*<<< orphan*/  u32; } ;
typedef  int /*<<< orphan*/  u16 ;
struct nvmf_connect_data {int /*<<< orphan*/  hostnqn; int /*<<< orphan*/  subsysnqn; void* cntlid; int /*<<< orphan*/  hostid; } ;
struct nvme_ctrl {int /*<<< orphan*/  connect_q; TYPE_3__* opts; int /*<<< orphan*/  cntlid; int /*<<< orphan*/  sqsize; } ;
struct TYPE_4__ {int /*<<< orphan*/  cattr; void* sqsize; void* qid; int /*<<< orphan*/  fctype; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ connect; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {TYPE_2__* host; int /*<<< orphan*/  subsysnqn; scalar_t__ disable_sqflow; } ;
struct TYPE_5__ {int /*<<< orphan*/  nqn; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int BLK_MQ_REQ_NOWAIT ; 
 int BLK_MQ_REQ_RESERVED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_CONNECT_DISABLE_SQFLOW ; 
 int /*<<< orphan*/  NVMF_NQN_SIZE ; 
 int __nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,union nvme_result*,struct nvmf_connect_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvmf_connect_data*) ; 
 struct nvmf_connect_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_fabrics_command ; 
 int /*<<< orphan*/  nvme_fabrics_type_connect ; 
 int /*<<< orphan*/  nvmf_log_connect_error (struct nvme_ctrl*,int,int /*<<< orphan*/ ,struct nvme_command*,struct nvmf_connect_data*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int nvmf_connect_io_queue(struct nvme_ctrl *ctrl, u16 qid, bool poll)
{
	struct nvme_command cmd;
	struct nvmf_connect_data *data;
	union nvme_result res;
	int ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.connect.opcode = nvme_fabrics_command;
	cmd.connect.fctype = nvme_fabrics_type_connect;
	cmd.connect.qid = cpu_to_le16(qid);
	cmd.connect.sqsize = cpu_to_le16(ctrl->sqsize);

	if (ctrl->opts->disable_sqflow)
		cmd.connect.cattr |= NVME_CONNECT_DISABLE_SQFLOW;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	uuid_copy(&data->hostid, &ctrl->opts->host->id);
	data->cntlid = cpu_to_le16(ctrl->cntlid);
	strncpy(data->subsysnqn, ctrl->opts->subsysnqn, NVMF_NQN_SIZE);
	strncpy(data->hostnqn, ctrl->opts->host->nqn, NVMF_NQN_SIZE);

	ret = __nvme_submit_sync_cmd(ctrl->connect_q, &cmd, &res,
			data, sizeof(*data), 0, qid, 1,
			BLK_MQ_REQ_RESERVED | BLK_MQ_REQ_NOWAIT, poll);
	if (ret) {
		nvmf_log_connect_error(ctrl, ret, le32_to_cpu(res.u32),
				       &cmd, data);
	}
	kfree(data);
	return ret;
}