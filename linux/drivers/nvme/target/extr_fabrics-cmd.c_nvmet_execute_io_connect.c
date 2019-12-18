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
typedef  int u16 ;
struct nvmf_connect_data {scalar_t__ cntlid; int /*<<< orphan*/  hostnqn; int /*<<< orphan*/  subsysnqn; } ;
struct nvmf_connect_command {scalar_t__ qid; scalar_t__ recfmt; } ;
struct nvmet_req {TYPE_4__* cqe; TYPE_1__* cmd; } ;
struct nvmet_ctrl {int /*<<< orphan*/  cntlid; TYPE_2__* subsys; } ;
struct TYPE_7__ {int /*<<< orphan*/  u16; int /*<<< orphan*/  u32; } ;
struct TYPE_8__ {TYPE_3__ result; } ;
struct TYPE_6__ {int max_qid; } ;
struct TYPE_5__ {struct nvmf_connect_command connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPO_IATTR_CONNECT_SQE (int) ; 
 int NVME_SC_CONNECT_FORMAT ; 
 int NVME_SC_CONNECT_INVALID_PARAM ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INTERNAL ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvmf_connect_data*) ; 
 struct nvmf_connect_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 
 int nvmet_copy_from_sgl (struct nvmet_req*,int /*<<< orphan*/ ,struct nvmf_connect_data*,int) ; 
 int nvmet_ctrl_find_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nvmet_req*,struct nvmet_ctrl**) ; 
 int /*<<< orphan*/  nvmet_ctrl_put (struct nvmet_ctrl*) ; 
 int nvmet_install_queue (struct nvmet_ctrl*,struct nvmet_req*) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nvmet_execute_io_connect(struct nvmet_req *req)
{
	struct nvmf_connect_command *c = &req->cmd->connect;
	struct nvmf_connect_data *d;
	struct nvmet_ctrl *ctrl = NULL;
	u16 qid = le16_to_cpu(c->qid);
	u16 status = 0;

	d = kmalloc(sizeof(*d), GFP_KERNEL);
	if (!d) {
		status = NVME_SC_INTERNAL;
		goto complete;
	}

	status = nvmet_copy_from_sgl(req, 0, d, sizeof(*d));
	if (status)
		goto out;

	/* zero out initial completion result, assign values as needed */
	req->cqe->result.u32 = 0;

	if (c->recfmt != 0) {
		pr_warn("invalid connect version (%d).\n",
			le16_to_cpu(c->recfmt));
		status = NVME_SC_CONNECT_FORMAT | NVME_SC_DNR;
		goto out;
	}

	status = nvmet_ctrl_find_get(d->subsysnqn, d->hostnqn,
				     le16_to_cpu(d->cntlid),
				     req, &ctrl);
	if (status)
		goto out;

	if (unlikely(qid > ctrl->subsys->max_qid)) {
		pr_warn("invalid queue id (%d)\n", qid);
		status = NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
		req->cqe->result.u32 = IPO_IATTR_CONNECT_SQE(qid);
		goto out_ctrl_put;
	}

	status = nvmet_install_queue(ctrl, req);
	if (status) {
		/* pass back cntlid that had the issue of installing queue */
		req->cqe->result.u16 = cpu_to_le16(ctrl->cntlid);
		goto out_ctrl_put;
	}

	pr_debug("adding queue %d to ctrl %d.\n", qid, ctrl->cntlid);

out:
	kfree(d);
complete:
	nvmet_req_complete(req, status);
	return;

out_ctrl_put:
	nvmet_ctrl_put(ctrl);
	goto out;
}