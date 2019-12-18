#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct nvmet_req {TYPE_3__* ops; scalar_t__ ns; TYPE_2__* cmd; TYPE_4__* cqe; TYPE_5__* sq; } ;
struct TYPE_10__ {int /*<<< orphan*/  qid; int /*<<< orphan*/  sqhd_disabled; } ;
struct TYPE_9__ {int /*<<< orphan*/  command_id; int /*<<< orphan*/  sq_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* queue_response ) (struct nvmet_req*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  command_id; } ;
struct TYPE_7__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_put_namespace (scalar_t__) ; 
 int /*<<< orphan*/  nvmet_set_error (struct nvmet_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_update_sq_head (struct nvmet_req*) ; 
 int /*<<< orphan*/  stub1 (struct nvmet_req*) ; 
 int /*<<< orphan*/  trace_nvmet_req_complete (struct nvmet_req*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __nvmet_req_complete(struct nvmet_req *req, u16 status)
{
	if (!req->sq->sqhd_disabled)
		nvmet_update_sq_head(req);
	req->cqe->sq_id = cpu_to_le16(req->sq->qid);
	req->cqe->command_id = req->cmd->common.command_id;

	if (unlikely(status))
		nvmet_set_error(req, status);

	trace_nvmet_req_complete(req);

	if (req->ns)
		nvmet_put_namespace(req->ns);
	req->ops->queue_response(req);
}