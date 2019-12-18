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
struct nvmet_req {TYPE_1__* sq; } ;
struct nvmet_ctrl {scalar_t__ nr_async_event_cmds; int /*<<< orphan*/  async_event_work; int /*<<< orphan*/  lock; struct nvmet_req** async_event_cmds; } ;
struct TYPE_2__ {struct nvmet_ctrl* ctrl; } ;

/* Variables and functions */
 scalar_t__ NVMET_ASYNC_EVENTS ; 
 int NVME_SC_ASYNC_LIMIT ; 
 int NVME_SC_DNR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void nvmet_execute_async_event(struct nvmet_req *req)
{
	struct nvmet_ctrl *ctrl = req->sq->ctrl;

	mutex_lock(&ctrl->lock);
	if (ctrl->nr_async_event_cmds >= NVMET_ASYNC_EVENTS) {
		mutex_unlock(&ctrl->lock);
		nvmet_req_complete(req, NVME_SC_ASYNC_LIMIT | NVME_SC_DNR);
		return;
	}
	ctrl->async_event_cmds[ctrl->nr_async_event_cmds++] = req;
	mutex_unlock(&ctrl->lock);

	schedule_work(&ctrl->async_event_work);
}