#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  tag; } ;
struct nvme_ns {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  command_id; } ;
struct nvme_command {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
#define  REQ_OP_DISCARD 134 
#define  REQ_OP_DRV_IN 133 
#define  REQ_OP_DRV_OUT 132 
#define  REQ_OP_FLUSH 131 
#define  REQ_OP_READ 130 
#define  REQ_OP_WRITE 129 
#define  REQ_OP_WRITE_ZEROES 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memcpy (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_clear_nvme_request (struct request*) ; 
 TYPE_2__* nvme_req (struct request*) ; 
 int /*<<< orphan*/  nvme_setup_discard (struct nvme_ns*,struct request*,struct nvme_command*) ; 
 int /*<<< orphan*/  nvme_setup_flush (struct nvme_ns*,struct nvme_command*) ; 
 int /*<<< orphan*/  nvme_setup_rw (struct nvme_ns*,struct request*,struct nvme_command*) ; 
 int /*<<< orphan*/  nvme_setup_write_zeroes (struct nvme_ns*,struct request*,struct nvme_command*) ; 
 int req_op (struct request*) ; 
 int /*<<< orphan*/  trace_nvme_setup_cmd (struct request*,struct nvme_command*) ; 

blk_status_t nvme_setup_cmd(struct nvme_ns *ns, struct request *req,
		struct nvme_command *cmd)
{
	blk_status_t ret = BLK_STS_OK;

	nvme_clear_nvme_request(req);

	memset(cmd, 0, sizeof(*cmd));
	switch (req_op(req)) {
	case REQ_OP_DRV_IN:
	case REQ_OP_DRV_OUT:
		memcpy(cmd, nvme_req(req)->cmd, sizeof(*cmd));
		break;
	case REQ_OP_FLUSH:
		nvme_setup_flush(ns, cmd);
		break;
	case REQ_OP_WRITE_ZEROES:
		ret = nvme_setup_write_zeroes(ns, req, cmd);
		break;
	case REQ_OP_DISCARD:
		ret = nvme_setup_discard(ns, req, cmd);
		break;
	case REQ_OP_READ:
	case REQ_OP_WRITE:
		ret = nvme_setup_rw(ns, req, cmd);
		break;
	default:
		WARN_ON_ONCE(1);
		return BLK_STS_IOERR;
	}

	cmd->common.command_id = req->tag;
	trace_nvme_setup_cmd(req, cmd);
	return ret;
}