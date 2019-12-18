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
struct nvmet_req {TYPE_4__* cmd; TYPE_2__* cq; TYPE_1__* sq; } ;
struct nvmet_ns {int /*<<< orphan*/  device_path; } ;
struct nvmet_ctrl {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  nsid; } ;
struct TYPE_8__ {TYPE_3__ rw; } ;
struct TYPE_6__ {scalar_t__ qid; } ;
struct TYPE_5__ {scalar_t__ qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_NAME_LEN ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nvmet_ns* nvmet_find_namespace (struct nvmet_ctrl*,int /*<<< orphan*/ ) ; 
 struct nvmet_ctrl* nvmet_req_to_ctrl (struct nvmet_req*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __assign_disk_name(char *name, struct nvmet_req *req,
		bool init)
{
	struct nvmet_ctrl *ctrl = nvmet_req_to_ctrl(req);
	struct nvmet_ns *ns;

	if ((init && req->sq->qid) || (!init && req->cq->qid)) {
		ns = nvmet_find_namespace(ctrl, req->cmd->rw.nsid);
		strncpy(name, ns->device_path, DISK_NAME_LEN);
		return;
	}

	memset(name, 0, DISK_NAME_LEN);
}